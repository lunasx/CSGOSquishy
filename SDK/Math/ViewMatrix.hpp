
/*MIT License

Copyright(c) 2020 Black

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


https://github.com/xBlack40/CSGOSquishy/blob/main/LICENSE */

#pragma once
#include "vector3d.hpp"

typedef float vec_t;

class view_matrix_t {
public:

	view_matrix_t();
	view_matrix_t(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);


	view_matrix_t(const vec3_t& forward, const vec3_t& left, const vec3_t& up);


	view_matrix_t(const matrix_t& matrix3x4);


	void		init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);


	void		init(const matrix_t& matrix3x4);


	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	
	inline float *base() {
		return &m[0][0];
	}

	inline const float *base() const {
		return &m[0][0];
	}

	void		set_left(const vec3_t &vLeft);
	void		set_up(const vec3_t &vUp);
	void		set_forward(const vec3_t &vForward);

	void		get_basis_vector_3d(vec3_t &vForward, vec3_t &vLeft, vec3_t &vUp) const;
	void		set_basis_vector_3d(const vec3_t &vForward, const vec3_t &vLeft, const vec3_t &vUp);


	vec3_t &	get_translation(vec3_t &vTrans) const;
	void		set_translation(const vec3_t &vTrans);

	void		pre_translate(const vec3_t &vTrans);
	void		post_translate(const vec3_t &vTrans);

	matrix_t&	as_matrix();
	const matrix_t& as_matrix() const;
	void		copy_from_matrix(const matrix_t &m3x4);
	void		set_matrix(matrix_t& matrix3x4) const;

	bool		operator==(const view_matrix_t& src) const;
	bool		operator!=(const view_matrix_t& src) const { return !(*this == src); }


	vec3_t		get_left() const;
	vec3_t		get_up() const;
	vec3_t		get_forward() const;
	vec3_t		get_translation() const;

	
public:

	void		vector_3d_multiply(const vec3_t &vIn, vec3_t &vOut) const;


	vec3_t		apply_rotation(const vec3_t &vVec) const;


	vec3_t		operator*(const vec3_t &vVec) const;


	vec3_t		vector_3d_multiply(const vec3_t &vVec) const;


	vec3_t		vector_3d_transpose_rotation(const vec3_t &vVec) const;


	vec3_t		vector_3d_multiply_upper(const vec3_t &vVec) const;


	vec3_t		vector_3d_transpose(const vec3_t &vVec) const;


public:

	view_matrix_t&	operator=(const view_matrix_t &mOther);

	void		MatrixMul(const view_matrix_t &vm, view_matrix_t &out) const;


	const view_matrix_t& operator+=(const view_matrix_t &other);


	view_matrix_t		operator*(const view_matrix_t &mOther) const;


	view_matrix_t		operator+(const view_matrix_t &other) const;
	view_matrix_t		operator-(const view_matrix_t &other) const;


	view_matrix_t		operator-() const;


public:

	void		identity();

	bool		is_identity() const;

	
	void		setup_maitrx_orginal_angles(const vec3_t &origin, const vec3_t &vAngles);

	void		inverse_tr(view_matrix_t &mRet) const;

	bool		is_rotation_matrix() const;

	view_matrix_t		inverse_tr() const;

	vec3_t		get_scale() const;

	view_matrix_t		scale(const vec3_t &vScale);

	view_matrix_t		normalize_basis_vector_3d() const;

	view_matrix_t		transpose() const;

	view_matrix_t		transpose_3x3() const;

public:

	vec_t		m[4][4];
};