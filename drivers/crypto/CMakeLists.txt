zephyr_link_interface_ifdef(CONFIG_MBEDTLS mbedTLS)
zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_CRYPTO_TINYCRYPT_SHIM	crypto_tc_shim.c)
zephyr_library_sources_ifdef(CONFIG_CRYPTO_ATAES132A		crypto_ataes132a.c)
zephyr_library_sources_ifdef(CONFIG_CRYPTO_MBEDTLS_SHIM		crypto_mtls_shim.c)
zephyr_library_link_libraries_ifdef(CONFIG_MBEDTLS mbedTLS)
