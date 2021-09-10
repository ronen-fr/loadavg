// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
#pragma once

#include <fcntl.h>

#include <string_view>

#include "welford_t.h"

// inline volatile int interval{1};

struct ScrubAverages {
  float load_per_cpu_{1.0f};
  float daily_{1.0};
  bool improving_{true};
};

class LoadBase {
 public:
  inline static constexpr const int daily_samples = 60;	 // * 24 * 24;
  // virtual void init(ScrubAverages& sav) = 0;
  virtual void update_averages() = 0;
  virtual ~LoadBase() = default;

  virtual void show(std::string_view title) = 0;

  virtual const ScrubAverages& get_scrub_avgs() = 0;
};

// a version based on rereading /proc/loadavg

class Fload : public LoadBase {
 private:
  welford_t welf_{10.0};

  int load_fd_{-1};

  // double daily_{1.0};
  int cpu_num_;
  ScrubAverages& sav_;

  // only for debugging:
  double avg_1m{1.1};
  double avg_5m{1.5};
  double avg_15m{1.15};

  void mark_failure();

 public:
  explicit Fload(ScrubAverages& sav);

  void update_averages() final;

  ~Fload() override;

  void show(std::string_view title) final;

  const ScrubAverages& get_scrub_avgs() final { return sav_; }
};



/*
ScrubQueue::ScrubQueue(CephContext* cct, OSDService& osds)
    : cct{cct}, osd_service{osds}
{
  // initialize the daily loadavg with current 15min loadavg
  if (double loadavgs[3]; getloadavg(loadavgs, 3) == 3) {
    daily_loadavg = loadavgs[2];
  } else {
    derr << "OSD::init() : couldn't read loadavgs\n" << dendl;
    daily_loadavg = 1.0;
  }
}
 std::optional<double> ScrubQueue::update_load_average()
{
 int hb_interval = cct->_conf->osd_heartbeat_interval;
 int n_samples = 60 * 24 * 24;
 if (hb_interval > 1) {
   n_samples /= hb_interval;
   if (n_samples < 1)
     n_samples = 1;
 }

// get CPU load avg
double loadavgs[1];
if (getloadavg(loadavgs, 1) == 1) {
 daily_loadavg = (daily_loadavg * (n_samples - 1) + loadavgs[0]) / n_samples;
 dout(17) << "heartbeat: daily_loadavg " << daily_loadavg << dendl;
 return 100 * loadavgs[0];
}

return std::nullopt;
}

bool ScrubQueue::scrub_load_below_threshold() const
{
  double loadavgs[3];
  if (getloadavg(loadavgs, 3) != 3) {
    dout(10) << __func__ << " couldn't read loadavgs\n" << dendl;
    return false;
  }

// allow scrub if below configured threshold
long cpus = sysconf(_SC_NPROCESSORS_ONLN);
double loadavg_per_cpu = cpus > 0 ? loadavgs[0] / cpus : loadavgs[0];
if (loadavg_per_cpu < cct->_conf->osd_scrub_load_threshold) {
  dout(20) << "loadavg per cpu " << loadavg_per_cpu << " < max "
	   << cct->_conf->osd_scrub_load_threshold << " = yes" << dendl;
  return true;
}

// allow scrub if below daily avg and currently decreasing
if (loadavgs[0] < daily_loadavg && loadavgs[0] < loadavgs[2]) {
  dout(20) << "loadavg " << loadavgs[0] << " < daily_loadavg "
	   << daily_loadavg << " and < 15m avg " << loadavgs[2] << " = yes"
	   << dendl;
  return true;
}

dout(20) << "loadavg " << loadavgs[0] << " >= max "
	 << cct->_conf->osd_scrub_load_threshold
	 << " and ( >= daily_loadavg " << daily_loadavg << " or >= 15m avg "
	 << loadavgs[2] << ") = no" << dendl;
return false;
}

 */