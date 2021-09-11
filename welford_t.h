// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
#pragma once
#include <cstdint>
#include <algorithm>

/*
initialize:
    m = 0;
    S = 0;
    n = 0;

 for each incoming sample x:
       prev_mean = m;
 n = n + 1;
 m = m + (x-m)/n;
 S = S + (x-m)*(x-prev_mean)
 */

template<typename FLT, uint64_t MAXSAMPLES>
struct welford_t {
  //inline static constexpr const uint64_t daily_samples = 60;	// * 24 * 24;

  welford_t(FLT frst) {
    m_ = frst;
    n_ = 1;
  }

  inline FLT nxt(FLT v)
  {
    n_ = std::min(n_+1, MAXSAMPLES);
    m_ = m_ + (v - m_) / n_;
    return m_;
  }

  FLT m_;
  uint64_t n_;
};

