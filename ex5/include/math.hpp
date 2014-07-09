# pragma once

# include <eigen/Core>
# include <eigen/Dense>

# include <cmath>

typedef double distance_type;

template< typename T, unsigned int Dim >
using vec_type = Eigen::Matrix< T, Dim, 1 >;

typedef vec_type< double, 3 > vec3_type;
