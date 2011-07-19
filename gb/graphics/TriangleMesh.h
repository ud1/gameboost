/** \file triangle_mesh.h

 � �� .. ����� ���������� ����������� ����.

 \todo: �������� ����� ����������, �����, ������ � ������ ��������, ���������.

*/


#pragma once

#include "../base/Types.h"
#include "Buffer.h"

#include <string>
#include <vector>

#include "../fmath/fmath.h"


/*
    ��������:
	 
	void create_sphere (std::vector<vertex>& vertexes, size_t sl, .......) {....}
	void create_cilinder(.......)
	void create_cube(.....)
	void create_plane(.......)
		

*/


namespace gb
{
	namespace graphics
	{



	template <typename T>
	struct  vertex_xyz
	{
	    T  x, y, z;
	};


	template <typename T>
	struct  normal_xyz
	{
	    T  x, y, z;
	};


	template <typename T>
	struct uv 
	{
	   T u, v;
	};



	template<typename T>
	struct vertex_n_tc
	{
		vertex_xyz<T> v_;
		normal_xyz<T> n_;
		        uv<T> uv_;
	};
	
	
	template<typename T, size_t TNumTexCoord>
	struct vertex_n_tcm
	{
		vertex_xyz  v;
		normal_xyz  n;
		uv texcoord[TNumTexCoord];
	};

 

	//------------------------------------------------------------

	// temp !
	template <typename T>
	inline void  normalize_vector3( T* pvec3 )
	{
	  T _x = pvec3[0];
	  T _y = pvec3[1];
	  T _z = pvec3[2];
	  
	  const T tlen = strt(_x*_x + _y*_y + _z*_z);
	  if(!tlen) return ;
	  _x /= tlen;
	  	  
	 pvec3[0] = _x;
	 pvec3[1] = _y;
	 pvec3[2] = _z; 
 
	}
	
		
	//-----------------------------------------------------------

//	typedef vertex_n_tc<float,1>   vertex;

 


// ��� ��������� !!!
// 
// 
// ��� ��� �� �� ������� �������.. ��   
class triangle_mesh {
public:

	// ���������� ���� (���������� � ����),  �� ��� ��� �����.
	struct mesh_info 
	{

		uint32_t  num_vertex; ///< ������� � ���� ������
		uint32_t  num_indexes; ///< ������� ��������.
		uint32_t  vertex_size; ///< ������ ������� � ������
	
	
	};



 fmath::AABB   get_boundingbox() const    { return m_Bbox; }
 fmath::Sphere get_boundingSphere() const { return m_BSphere; } 
 
 const mesh_info* get_mesh_info() const { return &m_mesh_info; };
 
 virtual const Buffer* get_vertex_buffer() const =0;
 virtual const Buffer* get_index_buffer() const =0; 

protected:

 fmath::AABB       m_Bbox;
 fmath::Sphere    m_BSphere;
 mesh_info 	m_mesh_info;
 
 
};






	}
}
