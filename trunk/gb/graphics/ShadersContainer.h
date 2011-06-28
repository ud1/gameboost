



#pragma once


class ShadersContainer {
public:

    virtual ~ShadersContainer() {}
	
	
  virtual int32_t setParameter(const char* name, const float* data, int num ) =0;
  virtual int32_t getParameter(const char* name,   float* data, int num ) =0;  

};