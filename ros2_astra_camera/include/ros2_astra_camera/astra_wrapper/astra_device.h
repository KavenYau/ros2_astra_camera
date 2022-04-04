/*
 * Copyright (c) 2013, Willow Garage, Inc.
 * Copyright (c) 2016, Orbbec Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *      Author: Tim Liu (liuhua@orbbec.com)
 */

#ifndef ASTRA_DEVICE_H
#define ASTRA_DEVICE_H

#include <openni2/OpenNI.h>

#include <thread>

// #include "OniCTypes.h"
#include "ros2_astra_camera/astra_wrapper/astra_device_type.h"
#include "ros2_astra_camera/astra_wrapper/astra_exception.h"
#include "ros2_astra_camera/astra_wrapper/astra_video_mode.h"
// #include <boost/shared_ptr.hpp>
// #include <boost/cstdint.hpp>
// #include <boost/bind.hpp>
// #include <boost/function.hpp>
// #include <boost/thread.hpp>
// #include <boost/chrono.hpp>
// #include <boost/bind.hpp>

#include <sensor_msgs/msg/image.hpp>
#include <string>
#include <vector>

namespace openni {
class Device;
class DeviceInfo;
class VideoStream;
class SensorInfo;
}  // namespace openni

namespace astra_camera {

typedef std::function<void(sensor_msgs::msg::Image::SharedPtr image)>
    FrameCallbackFunction;

class AstraFrameListener;

class AstraDevice {
 public:
  AstraDevice(const std::string& device_URI);
  virtual ~AstraDevice();

  const std::string getUri() const;
  const std::string getVendor() const;
  const std::string getName() const;
  uint16_t getUsbVendorId() const;
  uint16_t getUsbProductId() const;

  const std::string getStringID() const;

  bool isValid() const;

  bool hasIRSensor() const;
  bool hasColorSensor() const;
  bool hasDepthSensor() const;

  void startIRStream();
  void startColorStream();
  void startDepthStream();

  void stopAllStreams();

  void stopIRStream();
  void stopColorStream();
  void stopDepthStream();

  bool isIRStreamStarted();
  bool isColorStreamStarted();
  bool isDepthStreamStarted();

  bool isImageRegistrationModeSupported() const;
  void setImageRegistrationMode(bool enabled);
  void setDepthColorSync(bool enabled);

  const AstraVideoMode getIRVideoMode();
  const AstraVideoMode getColorVideoMode();
  const AstraVideoMode getDepthVideoMode();

  const std::vector<AstraVideoMode>& getSupportedIRVideoModes() const;
  const std::vector<AstraVideoMode>& getSupportedColorVideoModes() const;
  const std::vector<AstraVideoMode>& getSupportedDepthVideoModes() const;

  bool isIRVideoModeSupported(const AstraVideoMode& video_mode) const;
  bool isColorVideoModeSupported(const AstraVideoMode& video_mode) const;
  bool isDepthVideoModeSupported(const AstraVideoMode& video_mode) const;

  void setIRVideoMode(const AstraVideoMode& video_mode);
  void setColorVideoMode(const AstraVideoMode& video_mode);
  void setDepthVideoMode(const AstraVideoMode& video_mode);

  void setIRFrameCallback(FrameCallbackFunction callback);
  void setColorFrameCallback(FrameCallbackFunction callback);
  void setDepthFrameCallback(FrameCallbackFunction callback);

  float getIRFocalLength(int output_y_resolution) const;
  float getColorFocalLength(int output_y_resolution) const;
  float getDepthFocalLength(int output_y_resolution) const;
  float getBaseline() const;
  OBCameraParams getCameraParams() const;
  bool isCameraParamsValid();
  char* getSerialNumber();
  char* getDeviceType();
  OB_DEVICE_NO getDeviceTypeNo();
  int getColorGain() const;
  int getDepthGain() const;
  int getIRGain() const;
  int getColorExposure() const;
  int getDepthExposure() const;
  int getIRExposure() const;

  void setCameraParams(OBCameraParams param);
  void setColorGain(int gain);
  void setDepthGain(int gain);
  void setIRGain(int gain);
  void setColorExposure(int exposure);
  void setDepthExposure(int exposure);
  void setIRExposure(int exposure);
  void setLaser(bool enable);
  void setIRFlood(bool enable);
  void setLDP(bool enable);
  void setFan(bool enable);
  void setDistortioncal(bool enable);
  void setAeEnable(bool enable);
  void setColorAutoExposure(bool enable);
  void setDepthAutoExposure(bool enable);
  void setIRAutoExposure(bool enable);
  void setColorAutoWhiteBalance(bool enable);
  void setDepthAutoWhiteBalance(bool enable);
  void setIRAutoWhiteBalance(bool enable);
  void setColorMirror(bool enable);
  void setDepthMirror(bool enable);
  void setIRMirror(bool enable);

  void switchIRCamera(int cam);

  bool getColorAutoExposure() const;
  bool getDepthAutoExposure() const;
  bool getIRAutoExposure() const;
  bool getColorAutoWhiteBalance() const;
  bool getDepthAutoWhiteBalance() const;
  bool getIRAutoWhiteBalance() const;

  void setUseDeviceTimer(bool enable);

  void setKeepAlive(bool enable);

 protected:
  void shutdown();

  void keepAlive();

  std::shared_ptr<openni::VideoStream> getIRVideoStream() const;
  std::shared_ptr<openni::VideoStream> getColorVideoStream() const;
  std::shared_ptr<openni::VideoStream> getDepthVideoStream() const;

  std::thread keep_alive_thread;

  std::shared_ptr<openni::Device> openni_device_;
  std::shared_ptr<openni::DeviceInfo> device_info_;

  std::shared_ptr<AstraFrameListener> ir_frame_listener;
  std::shared_ptr<AstraFrameListener> color_frame_listener;
  std::shared_ptr<AstraFrameListener> depth_frame_listener;

  mutable std::shared_ptr<openni::VideoStream> ir_video_stream_;
  mutable std::shared_ptr<openni::VideoStream> color_video_stream_;
  mutable std::shared_ptr<openni::VideoStream> depth_video_stream_;

  mutable std::vector<AstraVideoMode> ir_video_modes_;
  mutable std::vector<AstraVideoMode> color_video_modes_;
  mutable std::vector<AstraVideoMode> depth_video_modes_;

  bool ir_video_started_;
  bool color_video_started_;
  bool depth_video_started_;

  bool image_registration_activated_;

  bool use_device_time_;

  bool keep_alive_;

  OBCameraParams m_CamParams;
  bool m_ParamsValid;
  char serial_number[12];
  char device_type[32];
  OB_DEVICE_NO device_type_no;
};

std::ostream& operator<<(std::ostream& stream, const AstraDevice& device);

}  // namespace astra_camera

#endif  // ASTRA_DEVICE_H
