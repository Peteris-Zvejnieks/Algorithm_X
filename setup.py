import inspect
import os
import sys
from pathlib import Path

import setuptools
import cmake_build_extension

__version__ = "0.0.1"
_name_ = "DancingLinks"

init_py = inspect.cleandoc(
    """
    import cmake_build_extension
    
    with cmake_build_extension.build_extension_env():
        from DancingLinks import DLX as _DLX_cpp

    class DLX(DLX_cpp):
        def __init__(self, primary_items: int, secondary_items: int = 0):
            super().__init__(primary_items, secondary_items)

        def __iter__(self):
            self.make_generator()
            return self
    """
)

CIBW_CMAKE_OPTIONS = []
if "CIBUILDWHEEL" in os.environ and os.environ["CIBUILDWHEEL"] == "1":
    if sys.platform == "linux":
        CIBW_CMAKE_OPTIONS += ["-DCMAKE_INSTALL_LIBDIR=lib"]

setuptools.setup(
    name = _name_,
    version = __version__,
    ext_modules=[
        cmake_build_extension.CMakeExtension(
            name=_name_,
            install_prefix="DancingLinks_cpp",
            expose_binaries=["bin/DancingLinks"],
            write_top_level_init=init_py,
            source_dir=str(Path(__file__).parent.absolute()),
            cmake_configure_options=[
                                        f"-DPython3_ROOT_DIR={Path(sys.prefix)}",
                                        "-DCALL_FROM_SETUP_PY:BOOL=ON",
                                        "-DBUILD_SHARED_LIBS:BOOL=OFF",
                                        "-DEXAMPLE_WITH_PYBIND11:BOOL=ON",
                                    ]
        )
    ],
    cmdclass=dict(build_ext=cmake_build_extension.BuildExtension),
)