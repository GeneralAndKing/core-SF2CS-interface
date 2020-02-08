#include <iostream>
#include "seeta/FaceDetector.h"


void hello(){
    seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
    int id = 0;
    seeta::ModelSetting FDModel( "./model/fd_2_00.dat", device, id );
    seeta::FaceDetector FD(FDModel);
    std::cout<<"hello"<<std::endl;
}