#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include <pat/pat.hpp>
using namespace pat;
using namespace std;
using namespace chrono;

//langford

//int main(){
//for(int n = 1; n < 18; n++){
//    default_solver solver( 3 * n );
//        int num = 0;
//        for ( auto i = 1u; i <= n; ++i )
//        {
//            for ( auto j = 1u; j <= 2u * n - 1u - i; ++j )
//            {
//                auto k = i + j + 1u;
//
//                assert( k <= 2u * n );
//                ++num;
//                solver.add_option( vector<uint32_t>{2 * n + i, j, k} );
//            }
//        }
//        steady_clock::time_point t1 = steady_clock::now();
//        const auto num_solutions = solver.solve();
//        steady_clock::time_point t2 = steady_clock::now();
//        duration<double> total_duration = t2 - t1;
//        cout<<  n <<" "<< total_duration.count() << endl;
//    }
//    return 0;
//}


//dags

//int main(){
//    for(int n = 1; n < 15; n++){
//        uint32_t secondary_items = ( n * ( n - 1 ) ) / 2;
//        default_solver solver(n + secondary_items );
//
//        auto offset = n;
//        for ( auto i = 1u; i <= n; ++i ){
//            /* only primary inputs */
//            solver.add_option( std::vector<uint32_t>{i} );
//
//            for ( auto j = 1u; j < i; ++j ){
//                /* two primary inputs */
//                solver.add_option( std::vector<uint32_t>{i, offset + j} );
//
//                for ( auto k = j + 1; k < i; ++k ){
//                    /* one primary input */
//                    solver.add_option( std::vector<uint32_t>{i, offset + j, offset + k} );
//                }
//            }
//
//            offset += i - 1;
//        }
//
//        steady_clock::time_point t1 = steady_clock::now();
//        const auto num_solutions = solver.solve();
//        steady_clock::time_point t2 = steady_clock::now();
//        duration<double> total_duration = t2 - t1;
//        cout<<  n <<" "<< total_duration.count() << endl;
//
//    }
//    return 0;
//}


int main(){
    default_solver solver_ = default_solver( 7 );
    solver_.add_option( std::vector<uint32_t>{3, 5} );
    solver_.add_option( std::vector<uint32_t>{1, 4, 7} );
    solver_.add_option( std::vector<uint32_t>{2, 3, 6} );
    solver_.add_option( std::vector<uint32_t>{1, 4, 6} );
    solver_.add_option( std::vector<uint32_t>{2, 7} );
    solver_.add_option( std::vector<uint32_t>{4, 5, 7} );
    solver_.add_option( std::vector<uint32_t>{5} );

//    auto solution = solver_.solve();
    for (auto solution_ : solver_.solve())
    {
        std::vector<uint32_t> solution = solution_;
        for(int j = 0; j < solution.size(); j++){
            cout << solution[j] << " ";
        }
        cout << endl;
    }
//    while(true){
//        auto solution = solver.solve();
//        for(int j = 0; j < solution.size(); j++){
//            cout << solution[j] << " ";
//        }
//        cout << endl;
//    }

//    vector< vector< uint32_t >> solutions;

//    auto num_solutions = solver.solve( [&solver, &solutions]( const auto& begin, const auto& end ) {
//                                           std::vector< uint32_t > solution;
//                                           for ( auto it = begin; it != end; ++it ){
//                                               solution.push_back(solver.option_index( *it ));
//                                           }
//                                           solutions.push_back(solution);
//                                           return true;
//                                       }
//    );
//
//

//    for(int i  = 0; i < solutions.size(); i++){
//        vector< uint32_t > solution = solutions[i];
//        for(int j = 0; j < solution.size(); j++){
//            cout << solution[j] << " ";
//        }
//        cout << endl;
//    }
    return 0;
}


