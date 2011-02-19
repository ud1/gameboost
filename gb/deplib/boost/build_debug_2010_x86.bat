@rem bjam runtime-link=static link=static threading=multi variant=debug
bjam runtime-link=shared link=static threading=multi variant=debug toolset=msvc-10.0 -j4
