#!/bin/bash

lin_cmd="-Wall -w -std=c++11 -o protobyteApp 
-I/usr/local/include
-L/usr/local/lib
src/proto_main.cpp ../Protobyte_v02/ProtoBounds.h ../Protobyte_v02/ProtoDimension3.h 
../Protobyte_v02/ProtoMath.cpp ../Protobyte_v02/ProtoColor4.h ../Protobyte_v02/ProtoPoint2.h 
../Protobyte_v02/ProtoPoint3.h ../Protobyte_v02/ProtoTuple2.h 
../Protobyte_v02/ProtoTuple3.h ../Protobyte_v02/ProtoUtility.cpp
../Protobyte_v02/ProtoTransformFunction.cpp ../Protobyte_v02/ProtoVector3.h 
../Protobyte_v02/ProtoVector4.h 
../Protobyte_v02/ProtoFace3.cpp ../Protobyte_v02/ProtoMatrix3.h 
../Protobyte_v02/ProtoShape3.cpp 
../Protobyte_v02/ProtoFrenetFrame.cpp ../Protobyte_v02/ProtoVertex3.cpp 
../Protobyte_v02/ProtoGeom3.cpp ../Protobyte_v02/ProtoTexture2.cpp 
../Protobyte_v02/ProtoWorld.cpp ../Protobyte_v02/ProtoToroid.cpp 
../Protobyte_v02/ProtoLight.cpp ../Protobyte_v02/ProtoCamera.cpp 
../Protobyte_v02/ProtoRenderer.cpp ../Protobyte_v02/ProtoTube.cpp 
../Protobyte_v02/ProtoCurve3.cpp ../Protobyte_v02/ProtoShader.cpp 
../Protobyte_v02/ProtoSpline3.cpp -lGLEW -lGL -lsfml-graphics -lsfml-window -lsfml-system"

OS=$(uname -s)

case $( uname -s ) in
Darwin) g++ $app_cmd;;
*) g++ $lin_cmd;;
esac

echo "********* Compilation Attempt End *********"
./protobyteApp


