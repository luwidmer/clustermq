#ifndef _COMMON_H_
#define _COMMON_H_

#include <Rcpp.h>
#include <chrono>
#include <string>
#include <thread>
#include <unordered_map>
#include "zmq.hpp"
#include "zmq_addon.hpp"

#if ! defined(ZMQ_BUILD_DRAFT_API) || \
    ! ZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 3, 0) || \
    ! CPPZMQ_VERSION >= ZMQ_MAKE_VERSION(4, 10, 0)
#define XSTR(x) STR(x)
#define STR(x) #x
#pragma message "libzmq version is: " XSTR(ZMQ_VERSION)
#pragma message "cppzmq version is: " XSTR(CPPZMQ_VERSION)
#ifdef ZMQ_BUILD_DRAFT_API
#pragma message "DRAFT API is available"
#else
#pragma message "DRAFT API is missing"
#endif
#error clustermq needs libzmq>=4.3.0 and cppzmq>=4.10.0 with DRAFT enabled
#endif

enum wlife_t {
    active,
    shutdown,
    error,
    proxy_cmd,
    proxy_error
};
const char* wlife_t2str(wlife_t status);
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
extern Rcpp::Function R_serialize;
extern Rcpp::Function R_unserialize;

void check_interrupt_fn(void *dummy);
int pending_interrupt();
zmq::message_t int2msg(int val);
zmq::message_t r2msg(SEXP data);
SEXP msg2r(zmq::message_t &msg, bool unserialize);
wlife_t msg2wlife_t(zmq::message_t &msg);

#endif // _COMMON_H_
