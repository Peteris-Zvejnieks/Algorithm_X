import inspect
import os
import sys
from pathlib import Path

import setuptools
import cmake_build_extension

__version__ = "0.0.2"
_name_ = "DancingLinks"

init_py = inspect.cleandoc(
    """
    from .DancingLinks_cpp import DLX

    class DLX(DLX):
        def __init__(self, primary_items: int, secondary_items: int = 0):
            super().__init__(primary_items, secondary_items)

        def __iter__(self):
            self.make_generator()
            return self
    """
)

setuptools.setup(
    name = _name_,
    version = __version__,
    ext_modules=[
        cmake_build_extension.CMakeExtension(
            name=_name_,
            install_prefix="DancingLinks",
            write_top_level_init=init_py,
            source_dir=str(Path(__file__).parent.absolute()),
            cmake_configure_options=[
                                        f"-DPython3_ROOT_DIR={Path(sys.prefix)}",
                                        "-DCALL_FROM_SETUP_PY:BOOL=ON",
                                        "-DBUILD_SHARED_LIBS:BOOL=ON",
                                        "-DEXAMPLE_WITH_PYBIND11:BOOL=ON",
                                    ]
        )
    ],
    cmdclass=dict(build_ext=cmake_build_extension.BuildExtension,),
)