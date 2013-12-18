/*!  \brief  ProtoMatrix3.h: 3D Matrix implementation
 Guaranteed to not be terribly fast or efficient!
 Default order : Column Major
 Use transpose to convert to Row Major Order
 ProtoMatrix3.h
 Protobyte Library v02
 
 Created by Ira on 12/16/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */


#ifndef PROTO_MATRIX3_H
#define	PROTO_MATRIX3_H

#include "ProtoVector3.h"
#include <cassert>


namespace ijg {
    
    // forward declaration for non-member ops
    template <class T> class ProtoMatrix3;
    
    /*****************************************************/
    /*            Non-Member Ops & Functions             */
    /*****************************************************/
    //M3*V3
    //returns V3
    template <typename T>
    ProtoVector3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoVector3<T>& rhs);
    
    //V3*M3 (convenience function, still default column major order)
    //returns V3
    template <typename T>
    ProtoVector3<T> operator*(const ProtoVector3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3*M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3*Sclr
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, T s);
    
    //Sclr*M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator*(T s, const ProtoMatrix3<T>& rhs);
    
    //M3+M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3-M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3+Sclr
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, T s);
    
    //Sclr+M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator+(T s, const ProtoMatrix3<T>& rhs);
    
    //M3-Sclr
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, T s);
    
    //Sclr-M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator-(T s, const ProtoMatrix3<T>& rhs);
    /**********************/
    /* END non-member ops */
    /**********************/
    
    
    /*************************************************/
    /*                Class Declaration              */
    /*************************************************/
    template <class T>
    class ProtoMatrix3 {
        
    public:
        enum MajorOrder {
            ROW_MAJOR,
            COLUMN_MAJOR
        };
        
        // cstrs
        // array vals should be packed: xyzwxyzw... for M*V
        // transpose if you need xxxxyyyy... for V*M.
        ProtoMatrix3<T>();
        ProtoMatrix3<T>(T data[9], MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix3<T>(const ProtoVector3<T>& row0, const ProtoVector3<T>& row1, const ProtoVector3<T>& row2, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix3<T>(const ProtoVector3<T> rows[3], MajorOrder order=COLUMN_MAJOR);
        
        // copy cstr | assignment op
        ProtoMatrix3<T>(const ProtoMatrix3<T>& mat);
        ProtoMatrix3<T>& operator=(const ProtoMatrix3<T>& mat);
        
        void identity();
        void transpose();
        T getDeterminent() const;
        ProtoVector3<T> getRow(int index) const;
        ProtoVector3<T> getColumn(int index) const;
        void setRow(int index, const ProtoVector3<T>& row);
        void setColumn(int index, const ProtoVector3<T>& column);
        ProtoVector3<T> getRotate(float theta, const ProtoVector3<T>& axis, const ProtoVector3<T>& vec);
    
        
        /*************************************************/
        /*            Member Ops & Functions             */
        /*************************************************/
        ProtoMatrix3<T>& operator*=(const ProtoMatrix3<T>& m4);
        ProtoMatrix3<T>& operator*=(T s);
        ProtoMatrix3<T>& operator/=(T s);
        ProtoMatrix3<T>& operator+=(const ProtoMatrix3<T>& m4);
        ProtoMatrix3<T>& operator-=(const ProtoMatrix3<T>& m4);
        
        T& operator[](unsigned index);
        T&	operator() ( int r, int c );
        
        
    private:
        float data[9];
        float data2D[3][3];
        void init();
        void determinent();
        T determ; // determinate
        MajorOrder order;
        
    };
    
    /**************************************/
    /*       END Class Declaration        */
    /**************************************/
    
    /*************************************************/
    /*                  Constructors                  */
    /**************************************************/
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3() {
        // set default to identity
        identity();
        
        init();
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(T data[9], MajorOrder order):
    order(order){
        // eventually transpose data[16] if packed for row major (pre-multiplication)
        for(int i=0; i<9; ++i){
            this->data[i] = data[i]; // can I do this using default asignment op this.data = data without copying pointer or overloading =?
        }
        
        init();
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(const ProtoVector3<T>& row0, const ProtoVector3<T>& row1, const ProtoVector3<T>& row2, MajorOrder order):
    order(order) {
        setRow(0, row0);
        setRow(1, row1);
        setRow(2, row2);
        
        init();
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(const ProtoVector3<T> rows[3], MajorOrder order):
    order(order) {
        setRow(0, rows[0]);
        setRow(1, rows[1]);
        setRow(2, rows[2]);
        
        init();
    }
    
    // copy cstr
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(const ProtoMatrix3<T>& mat){
        for(int i=0; i<9; ++i){
            data[i] = mat.data[i];
        }
        T determ = mat.determ; // determinate
        order = mat.order;
    }
    
    // assignment op
    template <class T>
    inline ProtoMatrix3<T>& ProtoMatrix3<T>::operator=(const ProtoMatrix3<T>& mat){
        if (this != &mat){
            for(int i=0; i<9; ++i){
                data[i] = mat.data[i];
            }
            T determ = mat.determ; // determinate
            order = mat.order;
        }
        return *this;
    }
    
    /**************************************/
    /*           END Constructors         */
    /**************************************/

    
    
    /*****************************************************/
    /*                  Member Functions                 */
    /*****************************************************/
    
    template <class T>
    void ProtoMatrix3<T>::init(){
        determinent();
    }
    
    template <class T>
    inline void ProtoMatrix3<T>::transpose() {
        T temp[9];
        for (int i=0; i<3; ++i) {
            for (int j=0, k=0; j<3; ++j, k+=3) {
                temp[i*3+j] = data[i+k];
            }
        }
        for(int i=0; i<9; ++i){
            data[i] = temp[i];
        }
    }
    
    // Laplace expansion method
    // from http://www.mathsisfun.com/algebra/matrix-determinant.html
    template <class T>
    inline void ProtoMatrix3<T>::determinent() {
        determ = data[0]*(data[4]*data[8]-data[5]*data[7]) - data[1]*(data[3]*data[8]-data[5]*data[6]) + data[2]*(data[3]*data[7]-data[4]*data[6]);
    }
    
    template <class T>
    inline void ProtoMatrix3<T>::identity() {
        // set 1's along diagonal
        for (int i =0; i <16; i++) {
            if (i % 5 == 0) {
                data[i] = 1;
            } else {
                data[i] = 0;
            }
        }
    }
    
    template <class T>
    inline T  ProtoMatrix3<T>::getDeterminent() const {
        return determ;
    }
    
   
    template <class T>
    inline void ProtoMatrix3<T>::setRow(int index, const ProtoVector3<T>& row) {
        data[index*3] = row.x;
        data[1+index*3] = row.y;
        data[2+index*3] = row.z;
    }
    
    template <class T>
    inline void ProtoMatrix3<T>::setColumn(int index, const ProtoVector3<T>& column) {
        data[index] = column.x;
        data[3+index] = column.y;
        data[6+index] = column.z;
    }
    
    template <class T>
    inline ProtoVector3<T> ProtoMatrix3<T>::getRow(int index) const {
        return ProtoVector3<T>(data[index*3+0], data[index*3+1], data[index*3+2]);
    }
    
    template <class T>
    inline ProtoVector3<T> ProtoMatrix3<T>::getColumn(int index) const {
        return ProtoVector3<T>(data[index+0], data[index+3], data[index+6]);
    }

    
    template <class T>
    inline ProtoVector3<T> ProtoMatrix3<T>::getRotate(float theta, const ProtoVector3<T>& axis, const ProtoVector3<T>& vec) {
        //std::cout << "vec in getRotate = " << vec << std::endl;
        float c = cos(theta);
        float s = sin(theta);
        // row 1
        data[0] = c + (axis.x * axis.x) * (1 - c);
        data[1] = axis.x * axis.y * (1 - c) - s * axis.z;
        data[2] = axis.z * axis.x * (1 - c) + s * axis.y;
        //row 2
        data[3] = axis.x * axis.y * (1 - c) + s * axis.z;
        data[4] = c + (axis.y * axis.y) * (1 - c);
        data[5] = axis.z * axis.y * (1 - c) - s * axis.x;
        //row 3
        data[6] = axis.x * axis.z * (1 - c) - s * axis.y;
        data[7] = axis.y * axis.z * (1 - c) + s * axis.x;
        data[8] = c + (axis.z * axis.z) * (1 - c);
        
        Vec3f temp;
        temp.x = vec.x * data[0] + vec.y * data[1] + vec.z * data[2];
        temp.y = vec.x * data[3] + vec.y * data[4] + vec.z * data[5];
        temp.z = vec.x * data[6] + vec.y * data[7] + vec.z * data[8];
        
        return temp;
    }

    
    /**************************************/
    /*       END Member Functions         */
    /**************************************/
    
    
    
    /*****************************************************/
    /*              Member Ops Implementation            */
    /*****************************************************/
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator*=(const ProtoMatrix3<T>& m4){
        
        T temp[16];
        temp[0] = *this[0]*m4[0] + *this[1]*m4[4] + *this[2]*m4[8] + *this[3]*m4[12];
        temp[1] = *this[0]*m4[1] + *this[1]*m4[5] + *this[2]*m4[9] + *this[3]*m4[13];
        temp[2] = *this[0]*m4[2] + *this[1]*m4[6] + *this[2]*m4[10] + *this[3]*m4[14];
        temp[3] = *this[0]*m4[3] + *this[1]*m4[7] + *this[2]*m4[11] + *this[3]*m4[15];
        
        temp[4] = *this[4]*m4[0] + *this[5]*m4[4] + *this[6]*m4[8] + *this[7]*m4[12];
        temp[5] = *this[4]*m4[1] + *this[5]*m4[5] + *this[6]*m4[9] + *this[7]*m4[13];
        temp[6] = *this[4]*m4[2] + *this[5]*m4[6] + *this[6]*m4[10] + *this[7]*m4[14];
        temp[7] = *this[4]*m4[3] + *this[5]*m4[7] + *this[6]*m4[11] + *this[7]*m4[15];
        
        temp[8] = *this[8]*m4[0] + *this[9]*m4[4] + *this[10]*m4[8] + *this[11]*m4[12];
        temp[9] = *this[8]*m4[1] + *this[9]*m4[5] + *this[10]*m4[9] + *this[11]*m4[13];
        temp[10] = *this[8]*m4[2] + *this[9]*m4[6] + *this[10]*m4[10] + *this[11]*m4[14];
        temp[11] = *this[8]*m4[3] + *this[9]*m4[7] + *this[10]*m4[11] + *this[11]*m4[15];
        
        temp[12] = *this[12]*m4[0] + *this[13]*m4[4] + *this[14]*m4[8] + *this[15]*m4[12];
        temp[13] = *this[12]*m4[1] + *this[13]*m4[5] + *this[14]*m4[9] + *this[15]*m4[13];
        temp[14] = *this[12]*m4[2] + *this[13]*m4[6] + *this[14]*m4[10] + *this[15]*m4[14];
        temp[15] = *this[12]*m4[3] + *this[13]*m4[7] + *this[14]*m4[11] + *this[15]*m4[15];
        
        for(int i=0; i<16; ++i){
            data[i] = temp[i];
        }
        return *this;
    }
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator*=(T s){
        for(int i=0; i<16; ++i){
            data[i] *= s;
        }
        return *this;
    }
    
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator/=(T s){
        for(int i=0; i<16; ++i){
            data[i] /= s;
        }
        return *this;
    }
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator+=(const ProtoMatrix3<T>& m4){
        for(int i=0; i<16; ++i){
            data[i] += m4[i];
        }
        return *this;
    }
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator-=(const ProtoMatrix3<T>& m4){
        for(int i=0; i<16; ++i){
            data[i] -= m4[i];
        }
        return *this;
    }
    
    template <typename T>
    inline T& ProtoMatrix3<T>::operator[](unsigned index){
        assert( index >= 0 && index <= 15 );
        return data[index];
    }
    
    template <typename T>
    T&	ProtoMatrix3<T>::operator() ( int r, int c ){
        int index = r*4+c;
        assert( index >= 0 && index <= 15 );
        return *this[index];
    }
    
    /**************************************/
    /*          END Member OPs           */
    /**************************************/
    
    
    /*****************************************************/
    /*         Non-Member Ops Implementation        */
    /*****************************************************/
    
    // M3*V3
    // returns V3
    template <typename T>
    inline ProtoVector3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoVector3<T>& rhs){
        T x = lhs[0]*rhs.x + lhs[1]*rhs.y + lhs[2]*rhs.z + lhs[3];
        T y = lhs[4]*rhs.x + lhs[5]*rhs.y + lhs[6]*rhs.z + lhs[7];
        T z = lhs[8]*rhs.x + lhs[9]*rhs.y + lhs[10]*rhs.z + lhs[11];
        return ProtoVector3<T>(x, y, z);
    }
    
    // V3*M3
    // returns V3
    template <typename T>
    inline ProtoVector3<T> operator*(const ProtoVector3<T>& lhs, const ProtoMatrix3<T>& rhs){
        return rhs*lhs;
    }
    
    // M3*M3
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs) {
        ProtoMatrix3<T> tempMat(T arr[9]);
        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
               //FIX tempMat.arr[i*3+j] = lhs[3*i]*rhs[j] + lhs[3*i+1]*rhs[j+4] + lhs[3*i+2]*rhs[j+8] + lhs[3*i+3]*rhs[j+12];
            }
        }
        return tempMat;
    }
    
    // M4*Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, T s) {
        ProtoMatrix3<T> tempMat(T arr[9]);
        for(int i=0; i<9; ++i){
            tempMat.arr[i] = lhs[i]*s;
        }
        return tempMat;
    }
    
    // Sclr*M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator*(T s, const ProtoMatrix3<T>& rhs) {
        return rhs*s;
    }
    
    // M4+M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs){
        ProtoMatrix3<T> tempMat(T arr[9]);
        for(int i=0; i<9; ++i){
            tempMat.arr[i] = lhs[i]+rhs[i];
        }
        return tempMat;
    }
    
    // M4-M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs){
        ProtoMatrix3<T> tempMat(T arr[9]);
        for(int i=0; i<9; ++i){
            tempMat.arr[i] = lhs[i]-rhs[i];
        }
        return tempMat;
    }
    
    // M4+Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, T s){
        ProtoMatrix3<T> tempMat(T arr[16]);
        for(int i=0; i<16; ++i){
            tempMat.arr[i] = lhs[i]+s;
        }
        return tempMat;
    }
    
    // Sclr+M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator+(T s, const ProtoMatrix3<T>& rhs){
        return rhs+s;
    }
    
    // M4-Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, T s){
        return lhs+(-s);
    }
    
    // Sclr-M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator-(T s, const ProtoMatrix3<T>& rhs){
        return rhs+(-s);
    }
    
    /**********************/
    /*         END        */
    /**********************/
    
    
    
    
#define ProtoMatrix3f ProtoMatrix3<float>
#define ProtoMatrix3d ProtoMatrix3<double>
}

#endif	// PROTO_MATRIX3_H

