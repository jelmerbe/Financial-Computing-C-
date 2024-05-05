#include <iostream>
#include <functional>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::vector<double> BVector;
using namespace std;

void exampleVector(){
  // constructing vectors
  BVector vec1, vec2(2);
  vec2[0]=1.3;
  vec2[1]=2.5;
  BVector vec3(vec2);
  cout << "vec1=" << vec1 <<endl;
  cout << "vec2=" << vec2 <<endl;
  cout << "vec3=" << vec3 <<endl;

  // +, +=, etc. operator
  BVector vec4=vec2+vec3;
  cout << "vec4=vec2+vec3=" << vec4 <<endl;
  cout << "(vec4*=3.0)=" << (vec4*=3.0) <<endl;

  // using stl algorithms on boost vectors
  BVector vec5(vec2.size());
  BVector::iterator bIter1 = vec2.begin();
  BVector::iterator eIter1 = vec2.end();
  BVector::iterator bIter2 = vec3.begin();
  BVector::iterator iter   = vec5.begin();
  std::transform(bIter1,
		 eIter1,
		 bIter2,
		 iter,
		 std::plus<double>());
  cout << "vec5 = " << vec5 << endl;

  // inner_prod, outer_prod, element_prod
  cout << "inner_prod(vec4,vec3)=" 
       << boost::numeric::ublas::inner_prod(vec4,vec3) << endl;
  cout << "outer_prod(vec4,vec3)=" 
       << boost::numeric::ublas::outer_prod(vec4,vec3) << endl;
  cout << "element_prod(vec4,vec3)=" 
       << boost::numeric::ublas::element_prod(vec4,vec3) << endl;

}

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

typedef boost::numeric::ublas::matrix<double> BMatrix;

void exampleMatrix(){

  //constructing matrices
  BMatrix mat1(3,4);
  for(unsigned int i=0; i<mat1.size1(); ++i) //defining entries
    for(unsigned int j=0; j<mat1.size2(); ++j)
      mat1(i,j)=i*j;
  cout << "mat1=" << mat1 << endl;
  cout << "mat1.size1()=" << mat1.size1() << endl;
  cout << "mat1.size2()=" << mat1.size2() << endl;
  BMatrix mat2(mat1); //copy constructor
  cout << "mat2=" << mat2 << endl;
  mat2.resize(3,3); //resizing the matrix
  cout << "mat2=" << mat2 << endl;

  // simple operations
  BMatrix mat3(mat2*3);
  cout << "mat3=" << mat3 << endl;
  cout << "mat3+=mat2" << (mat3+=mat2) << endl;
  cout << "mat3/=2.0" << (mat3/=2.0) << endl;

  // products
  BVector e1(boost::numeric::ublas::unit_vector<double>(3,0));
  cout << "mat3=" << mat3 << endl;
  cout << "e1=" << e1 << endl;
  cout << "mat3*e1=" << prod(mat3,e1) << endl;
  cout << "mat3*mat3=" << prod(mat3,mat3) << endl;

  //iterators
  cout << "mat3=" << mat3 << endl;
  BMatrix::iterator1 iter1=mat3.begin1();
  (*iter1)+=1.0;
  cout << "mat3=" << mat3 << endl;
  ++iter1;
  (*iter1)+=1.0;
  cout << "mat3=" << mat3 << endl;
  BMatrix::iterator2 iter2(mat3.begin2());
  (*iter2)+=1.0;
  cout << "mat3=" << mat3 << endl;
  ++iter2;
  (*iter2)+=1.0;
  cout << "mat3=" << mat3 << endl;
  BMatrix::iterator1 iter12(iter2.begin());
  (*iter12)+=1.0;
  cout << "mat3=" << mat3 << endl;
  ++iter12;
  (*iter12)+=1.0;
  cout << "mat3=" << mat3 << endl;


  typedef boost::numeric::ublas::matrix_row<BMatrix> BMatrixRow;
  typedef boost::numeric::ublas::matrix_column<BMatrix> BMatrixCol;

  BMatrixRow matrow1(mat3,1);
  BMatrixCol matcol1(mat3,0);
  cout << "mat3=" << mat3 << endl;
  cout << "row 1 of mat3=" << matrow1 << endl;
  cout << "col 0 of mat3=" << matcol1 << endl;
  matrow1(1)=10;
  cout << "row 1 of mat3=" << matrow1 << endl;
  cout << "mat3=" << mat3 << endl;
  matrow1*=10;
  cout << "row 1 of mat3=" << matrow1 << endl;
  cout << "mat3=" << mat3 << endl;
  matcol1(1)=0.1;
  cout << "col 0 of mat3=" << matcol1 << endl;
  cout << "mat3=" << mat3 << endl;
  matcol1*=0.1;
  cout << "col 0 of mat3=" << matcol1 << endl;
  cout << "mat3=" << mat3 << endl;
  std::fill(matrow1.begin(),matrow1.end(),3.14);
  cout << "row 1 of mat3=" << matrow1 << endl;
  cout << "mat3=" << mat3 << endl;
}


#include <boost/numeric/ublas/lu.hpp>

void exampleLinearEquation(){
  BMatrix A(2,2);
  A(0,0)=1;
  A(0,1)=1;
  A(1,0)=1;
  A(1,1)=0;
  BVector b(2);
  b(0)=5;
  b(1)=2;
  cout << "A=" << A << endl;
  cout << "b=" << b << endl;
  //solving Ax=b
    boost::numeric::ublas::lu_factorize(A);
  cout << "A=" << A << endl;
  boost::numeric::ublas::lu_substitute<const BMatrix,BVector>(A,b);
  cout << "b=" << b << endl;
  //solving A*Ainv=Identity
    BMatrix Ainv(boost::numeric::ublas::identity_matrix<double>(2));
  cout << "Ainv=" << Ainv << endl;
  boost::numeric::ublas::lu_substitute<const BMatrix,BMatrix>(A,Ainv);
  cout << "Ainv=" << Ainv << endl;
}

int main(){
  exampleVector();
  exampleMatrix();
  exampleLinearEquation();
  return 0;
}

/*
  vec1=[0]()
  vec2=[2](1.3,2.5)
  vec3=[2](1.3,2.5)
  vec4=vec2+vec3=[2](2.6,5)
  (vec4*=3.0)=[2](7.8,15)
  vec5 = [2](2.6,5)
  inner_prod(vec4,vec3)=47.64
  outer_prod(vec4,vec3)=[2,2]((10.14,19.5),(19.5,37.5))
  element_prod(vec4,vec3)=[2](10.14,37.5)
  mat1=[3,4]((0,0,0,0),(0,1,2,3),(0,2,4,6))
  mat1.size1()=3
  mat1.size2()=4
  mat2=[3,4]((0,0,0,0),(0,1,2,3),(0,2,4,6))
  mat2=[3,3]((0,0,0),(0,1,2),(0,2,4))
  mat3=[3,3]((0,0,0),(0,3,6),(0,6,12))
  mat3+=mat2[3,3]((0,0,0),(0,4,8),(0,8,16))
  mat3/=2.0[3,3]((0,0,0),(0,2,4),(0,4,8))
  mat3=[3,3]((0,0,0),(0,2,4),(0,4,8))
  e1=[3](1,0,0)
  mat3*e1=[3](0,0,0)
  mat3*mat3=[3,3]((0,0,0),(0,20,40),(0,40,80))
  mat3=[3,3]((0,0,0),(0,2,4),(0,4,8))
  mat3=[3,3]((1,0,0),(0,2,4),(0,4,8))
  mat3=[3,3]((1,0,0),(1,2,4),(0,4,8))
  mat3=[3,3]((2,0,0),(1,2,4),(0,4,8))
  mat3=[3,3]((2,1,0),(1,2,4),(0,4,8))
  mat3=[3,3]((2,2,0),(1,2,4),(0,4,8))
  mat3=[3,3]((2,2,0),(1,3,4),(0,4,8))
  mat3=[3,3]((2,2,0),(1,3,4),(0,4,8))
  row 1 of mat3=[3](1,3,4)
  col 0 of mat3=[3](2,1,0)
  row 1 of mat3=[3](1,10,4)
  mat3=[3,3]((2,2,0),(1,10,4),(0,4,8))
  row 1 of mat3=[3](10,100,40)
  mat3=[3,3]((2,2,0),(10,100,40),(0,4,8))
  col 0 of mat3=[3](2,0.1,0)
  mat3=[3,3]((2,2,0),(0.1,100,40),(0,4,8))
  col 0 of mat3=[3](0.2,0.01,0)
  mat3=[3,3]((0.2,2,0),(0.01,100,40),(0,4,8))
  row 1 of mat3=[3](3.14,3.14,3.14)
  mat3=[3,3]((0.2,2,0),(3.14,3.14,3.14),(0,4,8))
  A=[2,2]((1,1),(1,0))
  b=[2](5,2)
  A=[2,2]((1,1),(1,-1))
  b=[2](2,3)
  Ainv=[2,2]((1,0),(0,1))
  Ainv=[2,2]((0,1),(1,-1))
*/
