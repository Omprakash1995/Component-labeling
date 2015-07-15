#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include<iostream>
#include<fstream>
#include<CL/cl.hpp>
#include "Input.h"
using namespace std;
using namespace cl;


int Connected_components(char* fn, char* option)
{

	int height, width, cx, cy, td, cc = 0, labelindex = -0;
	char buf[256];

	if (read_header(fn, &width, &height, option) != 1)
	{
		return -1;
	}
	cout << height << " " << width << endl;
	cl_platform_id* platform_id;
	platform_id = new cl_platform_id[2];
	clGetPlatformIDs(2, platform_id, NULL);
	char* platform_name;
	::size_t infosize;
	clGetPlatformInfo(platform_id[0], CL_PLATFORM_NAME, 0, NULL,&infosize);
	platform_name = (char*)malloc(infosize);
	clGetPlatformInfo(platform_id[0], CL_PLATFORM_NAME, infosize, platform_name, 0);
	cout << platform_name<<endl;
	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id[0], 0 };

	Context context(CL_DEVICE_TYPE_GPU,properties);
	
	vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
	cout << devices.size();
	devices.resize(1);

	string device_name = devices[0].getInfo<CL_DEVICE_NAME>();

	cout << "Device Name:" << device_name << endl;
	
	cl_int comp_units = devices[0].getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
	cout << "No. of compute units:" << comp_units << endl;
	return 1;
}

