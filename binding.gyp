{
    "conditions": [
        [ 'OS=="win"', {
            'variables': {
                'boost_root%': 'C:/Libraries/boost_1_63_0',
            },

            'conditions': [
                ['target_arch=="x64"', {
                    'variables': {
                        'boostlib_root%': '<(boost_root)/lib64-msvc-14.0',
                        'libtorrent_root%': 'C:/Libraries/Rasterbar-libtorrent/msvc-14.0/x64',
                        'openssl_root%': 'C:/OpenSSL-Win64'
                    },
                }, {
                    'variables': {
                        'boostlib_root%': '<(boost_root)/lib32-msvc-14.0',
                        'libtorrent_root%': 'C:/Libraries/Rasterbar-libtorrent/msvc-14.0/x86',
                        'openssl_root%': 'C:/OpenSSL-Win32'
                    },
                }],
            ]
        }]
    ],

    "targets": [
        {
            "target_name": "<(module_name)",
            "sources": [
                "src/libtorrent.cc",
                "src/add_torrent_params.cc",
                "src/alert_types.cc",
                "src/bdecode.cc",
                "src/bencode.cc",
                "src/create_torrent.cc",
                "src/entry.cc",
                "src/file_storage.cc",
                "src/read_resume_data.cc",
                "src/session.cc",
                "src/settings_pack.cc",
                "src/torrent_handle.cc",
                "src/torrent_info.cc",
                "src/torrent_status.cc"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
            "defines": [
                "BOOST_ALL_NO_LIB",
                "NOMINMAX",
                "TORRENT_NO_DEPRECATE",
                "TORRENT_USE_OPENSSL"
            ],
            "cflags": [ "-std=c++11" ],
            "cflags_cc": [ "-std=c++11" ],
            "xcode_settings": {
                "OTHER_CPLUSPLUSFLAGS": [ '-std=c++11', '-stdlib=libc++' ],
                "OTHER_LDFLAGS": [ '-stdlib=libc++' ],
                "MACOSX_DEPLOYMENT_TARGET": '10.9'
            },
            "conditions": [
                [ 'OS=="win"', {
                    'configurations': {
                        'Debug': {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    "ExceptionHandling": 1,
                                    "RuntimeTypeInfo": 'true',
                                    "AdditionalOptions": [ "/FI malloc.h" ]
                                },
                            }
                        }, # Debug
                        'Release': {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    "ExceptionHandling": 1,
                                    "RuntimeTypeInfo": 'true',
                                    "AdditionalOptions": [ "/FI malloc.h" ]
                                },
                            },
                        }, # Release
                    }, # configurations
                    "copies": [{
                        'destination': '<(module_root_dir)/build/Release',
                        'files': ['<(openssl_root)/libcrypto-1_1-x64.dll','<(openssl_root)/libssl-1_1-x64.dll']
                    }],
                    "defines": [
                        "_CRT_SECURE_NO_DEPRECATE",
                        "_FILE_OFFSET_BITS=64",
                        "_SCL_SECURE_NO_DEPRECATE",
                        "_SCL_SECURE_NO_WARNINGS",
                        "_UNICODE",
                        "_WIN32",
                        "_WIN32_WINNT=0x0600",
                        "UNICODE",
                        "WIN32",
                        "WIN32_LEAN_AND_MEAN"
                    ],
                    "include_dirs" : [
                        "<(libtorrent_root)/include",
                        '<(boost_root)/',
                        '<(openssl_root)/include',
                    ],
                    "libraries": [
                        '-l<(libtorrent_root)/lib/libtorrent.lib',
                        '-l<(boostlib_root)/libboost_system-vc140-mt-s-1_63_0.lib',
                        '-l<(openssl_root)/lib/libcrypto.lib',
                        '-l<(openssl_root)/lib/libssl.lib',
                        '-liphlpapi'
                    ]
                },
                  'OS=="mac"', {
                    "libraries": [
                        "/usr/local/lib/libboost_system.a",
                        "$(HOME)/libtorrent/lib/libtorrent-rasterbar.a"
                    ]
                },
                  'OS=="linux"', {
                    "libraries": [
                        "$(HOME)/boost/lib/libboost_system.a",
                        "$(HOME)/libtorrent/lib/libtorrent-rasterbar.a"
                    ]
                }]
            ]
        },
        {
            "target_name": "post_build_action",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                    "destination": "<(module_path)"
                }
            ],
            "conditions": [
                [ 'OS=="win"', {
                    "copies": [
                        {
                            "files": [ '<(openssl_root)/libcrypto-1_1-x64.dll','<(openssl_root)/libssl-1_1-x64.dll' ],
                            "destination": "<(module_path)"
                        }
                    ]
                }]
            ]
        }
    ]
}
