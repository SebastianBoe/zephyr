if(CONFIG_HAS_NORDIC_DRIVERS)
  zephyr_include_directories(drivers)

  add_subdirectory(drivers)
endif()

if(CONFIG_HAS_NRFX)

  if(manifest_nrfx_type_download)
    # TODO: Fix
    include(DownloadProject)

    download_project(
      PROJ                project_nrfx
#      QUIET
      GIT_REPOSITORY      ${manifest_nrfx_type_download_repo}
      GIT_REF             ${manifest_nrfx_type_download_ref}
      GIT_SHA             ${manifest_nrfx_type_download_sha}
      GIT_SHALLOW         1
      GIT_CACHE_DIR       /home/sebo/.cache/zephyr/git
      )

    set(nrfx_SOURCE_DIR ${project_nrfx_SOURCE_DIR})
  elseif(manifest_nrfx_type_local)

    set(nrfx_SOURCE_DIR ${manifest_nrfx_type_local_path})
  else()
    assert(0 "Invalid manifest")
  endif()


  zephyr_include_directories(${nrfx_SOURCE_DIR})
  zephyr_include_directories(${nrfx_SOURCE_DIR}/drivers/include)
  zephyr_include_directories(${nrfx_SOURCE_DIR}/hal)
  zephyr_include_directories(${nrfx_SOURCE_DIR}/mdk)
  zephyr_include_directories(.)

  zephyr_sources_ifdef(CONFIG_NRFX_PRS   ${nrfx_SOURCE_DIR}/drivers/prs/nrfx_prs.c)

  zephyr_sources_ifdef(CONFIG_NRFX_ADC   ${nrfx_SOURCE_DIR}/drivers/src/nrfx_adc.c)
  zephyr_sources_ifdef(CONFIG_NRFX_PWM   ${nrfx_SOURCE_DIR}/drivers/src/nrfx_pwm.c)
  zephyr_sources_ifdef(CONFIG_NRFX_RTC   ${nrfx_SOURCE_DIR}/drivers/src/nrfx_rtc.c)
  zephyr_sources_ifdef(CONFIG_NRFX_SAADC ${nrfx_SOURCE_DIR}/drivers/src/nrfx_saadc.c)
  zephyr_sources_ifdef(CONFIG_NRFX_SPI   ${nrfx_SOURCE_DIR}/drivers/src/nrfx_spi.c)
  zephyr_sources_ifdef(CONFIG_NRFX_SPIM  ${nrfx_SOURCE_DIR}/drivers/src/nrfx_spim.c)
  zephyr_sources_ifdef(CONFIG_NRFX_TWI   ${nrfx_SOURCE_DIR}/drivers/src/nrfx_twi.c)
  zephyr_sources_ifdef(CONFIG_NRFX_TWIM  ${nrfx_SOURCE_DIR}/drivers/src/nrfx_twim.c)
  zephyr_sources_ifdef(CONFIG_NRFX_UART  ${nrfx_SOURCE_DIR}/drivers/src/nrfx_uart.c)
  zephyr_sources_ifdef(CONFIG_NRFX_UARTE ${nrfx_SOURCE_DIR}/drivers/src/nrfx_uarte.c)
  zephyr_sources_ifdef(CONFIG_NRFX_WDT   ${nrfx_SOURCE_DIR}/drivers/src/nrfx_wdt.c)
endif()
