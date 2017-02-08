if(CONFIG_INT_LATENCY_BENCHMARK)
  list(APPEND EXTRA_SRCS int_latency_bench.c)
endif()

if(CONFIG_STACK_CANARIES)
  list(APPEND EXTRA_SRCS compiler_stack_protect.c)
endif()

if(CONFIG_SYS_CLOCK_EXISTS)
  list(APPEND EXTRA_SRCS timer.c)
endif()

if(CONFIG_LEGACY_KERNEL)
  list(APPEND EXTRA_SRCS legacy_timer.c)
endif()

if(CONFIG_ATOMIC_OPERATIONS_C)
  list(APPEND EXTRA_SRCS atomic_c.c)
endif()

if(CONFIG_POLL)
  list(APPEND EXTRA_SRCS poll.c)
endif()

add_library(kernel
  alert.c
  device.c
  errno.c
  idle.c
  init.c
  legacy_offload.c
  mailbox.c
  mem_pool.c
  mem_pool.c
  mem_slab.c
  msg_q.c
  mutex.c
  pipes.c
  sched.c
  sem.c
  stack.c
  system_work_q.c
  queue.c
  sys_clock.c
  thread.c
  thread_abort.c
  work_q.c
  ${PROJECT_BINARY_DIR}/include/generated/version.h
  ${EXTRA_SRCS}
)

add_dependencies(kernel offsets_h)

target_sources(zephyr PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/version.c
)
target_link_libraries(kernel zephyr)
