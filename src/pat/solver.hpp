/* pat: C++ dancing links solver
 * Copyright (C) 2017  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
  \file solver.hpp
  \brief Solver interface

  \author Mathias Soeken
*/

#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cppcoro/generator.hpp>

#include <range/v3/action/join.hpp>
#include <range/v3/core.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/zip_with.hpp>

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pat
{

    struct item
    {
        uint32_t index{};
        uint32_t llink{};
        uint32_t rlink{};
    };

    struct node
    {
        union {
            int32_t len{};
            int32_t top;
        };
        uint32_t ulink{};
        uint32_t dlink{};
    };

    template<typename ItemSelectionFn>
    class solver
    {
        cppcoro::generator<std::vector<uint32_t>> generator;
        cppcoro::detail::generator_iterator<std::vector<uint32_t> > iter;
        cppcoro::detail::generator_sentinel end;
    public:
        explicit solver( const uint32_t primary_items, const uint32_t secondary_items = 0u)
                : items( primary_items + secondary_items + 1 ),
                  nodes( primary_items + secondary_items + 2 ),
                  primary_items( primary_items ),
                  secondary_items( secondary_items ),
                  num_items( primary_items + secondary_items )
        {
            initialize_items();
        }

        void add_option(std::vector<uint32_t> opt_items)
        {

            /*Error checking*/
            std::stable_sort(opt_items.begin(),  opt_items.end());
            bool containsDuplicates = (std::unique( opt_items.begin(),  opt_items.end()) !=  opt_items.end());

            if (containsDuplicates) throw pybind11::value_error("Subset must only contain unique values");
            if (* opt_items.begin() == 0u) throw pybind11::value_error("Elements must range from 1");
            if (opt_items.back() > num_items) throw pybind11::value_error("Elements cant be larger than size");

            /* store current last item */
            const auto p = nodes.size() - 1;
            auto k = 0u;

            for ( auto j : opt_items )
            {
                nodes[j].len++;
                const auto q = nodes[j].ulink;
                nodes[j].ulink = nodes[q].dlink = nodes.size();

                node next_node;
                next_node.ulink = q;
                next_node.dlink = j;
                next_node.top = j;

                nodes.push_back( next_node );
                ++k;
            }

            ++m;
            nodes[p].dlink = p + k;

            /* next spacer */
            node spacer;
            spacer.top = -m;
            spacer.ulink = p + 1;
            nodes.push_back( spacer );
        }

        void make_generator(){
            generator = this->solve();
            iter = generator.begin();
            end = generator.end();
        }

        std::vector<uint32_t> get_next(){
            if (iter == end) throw py::stop_iteration("end reached");
            py::gil_scoped_release release;
            std::vector<uint32_t> solution = *iter;
            ++iter;
            return solution;
        }

        std::vector<std::vector<uint32_t>> get_next_batch(uint32_t num = 100u){
            if (iter == end) throw py::stop_iteration("end reached");
            py::gil_scoped_release release;
            std::vector<std::vector<uint32_t>> solutions;
            for(uint32_t i = 0; i < num; i++){
                if (iter == end) break;
                std::vector<uint32_t> solution = *iter;
                solutions.push_back(std::move(solution));
                ++iter;
            }
            return solutions;
        }

        uint32_t get_number_of_solutions(){
            uint32_t number_of_solutions = 0;
            for (std::vector<uint32_t> solution : solve()){
                number_of_solutions ++;
            }
            return number_of_solutions;
        }

        cppcoro::generator<std::vector<uint32_t>> solve()
        {
            uint32_t l = 0, i = 0;
            std::vector<uint32_t> xs( items.size() );

            while ( true )
            {
//                 all items have been chosen
                if ( items[0].rlink == 0 )
                {
                    std::vector< uint32_t > solution;
                    for ( auto it = xs.cbegin(); it != xs.cbegin() + l; ++it ){
                      solution.push_back(option_index( *it ));
                    }
                    co_yield solution;
                    goto check_last;
                }

//                 choose next item i
                i = item_selection( items, nodes );

//                 cover i
                cover( i );
                xs[l] = nodes[i].dlink;

                while ( xs[l] == i )  //we tried all options for item i
                {
                    uncover( i );

                    check_last:
                    if ( l == 0 )
                        co_return;

//                     uncovers items in option
                    --l;
                    uncover_option( xs[l] );

//                     next i
                    i = nodes[xs[l]].top;
                    xs[l] = nodes[xs[l]].dlink;
                }

//                 cover items in option
                cover_option( xs[l] );
                ++l;
            }

//             we'll never reach here
        }

        inline uint32_t option_index( uint32_t i )
        {
            auto q = i - 1;
            while ( nodes[q].top > 0 )
            {
                --q;
            }
            return -nodes[q].top;
        }

    private:
        void initialize_items()
        {
            /* initialize linked list of top items */
            for ( auto i = 1u; i <= num_items; ++i )
            {
                items[i].index = i;
                items[i].llink = i - 1;
                items[i - 1].rlink = i;

                nodes[i].len = 0;
                nodes[i].ulink = nodes[i].dlink = i;
            }

            items[0].llink = primary_items;
            items[primary_items].rlink = 0;
            if ( secondary_items != 0 )
            {
                items[primary_items + 1].llink = num_items;
                items[num_items].rlink = primary_items + 1;
            }

            /* spacer */
            nodes[num_items + 1].top = 0;
        }

        inline void cover( uint32_t i )
        {
            auto p = nodes[i].dlink;
            while ( p != i )
            {
                hide( p );
                p = nodes[p].dlink;
            }

            /* dancing links */
            const auto l = items[i].llink;
            const auto r = items[i].rlink;
            items[l].rlink = r;
            items[r].llink = l;
        }

        inline void uncover( uint32_t i )
        {
            const auto l = items[i].llink;
            const auto r = items[i].rlink;
            items[l].rlink = i;
            items[r].llink = i;
            auto p = nodes[i].ulink;
            while ( p != i )
            {
                unhide( p );
                p = nodes[p].ulink;
            }
        }

        inline void hide( uint32_t i )
        {
            auto q = i + 1;

            while ( q != i )
            {
                auto x = nodes[q].top;
                const auto u = nodes[q].ulink;
                const auto d = nodes[q].dlink;
                if ( x <= 0 )
                {
                    q = u;
                }
                else
                {
                    nodes[u].dlink = d;
                    nodes[d].ulink = u;
                    nodes[x].len--;
                    ++q;
                }
            }
        }

        inline void unhide( uint32_t i )
        {
            auto q = i - 1;

            while ( q != i )
            {
                auto x = nodes[q].top;
                const auto u = nodes[q].ulink;
                const auto d = nodes[q].dlink;
                if ( x <= 0 )
                {
                    q = d;
                }
                else
                {
                    nodes[u].dlink = q;
                    nodes[d].ulink = q;
                    nodes[x].len++;
                    --q;
                }
            }
        }

        inline void cover_option( uint32_t i )
        {
            auto p = i + 1;
            while ( p != i )
            {
                auto j = nodes[p].top;
                if ( j <= 0 )
                {
                    p = nodes[p].ulink;
                }
                else
                {
                    cover( j );
                    ++p;
                }
            }
        }

        inline void uncover_option( uint32_t i )
        {
            auto p = i - 1;
            while ( p != i )
            {
                auto j = nodes[p].top;
                if ( j <= 0 )
                {
                    p = nodes[p].dlink;
                }
                else
                {
                    uncover( j );
                    --p;
                }
            }
        }

    private:
        std::vector<item> items;
        std::vector<node> nodes;

        uint32_t primary_items;
        uint32_t secondary_items;
        uint32_t num_items;
        int32_t m = 0;

        ItemSelectionFn&& item_selection = std::move( item_selection );
    };
}
