
//**************************************************************
//**************************************************************
// Implementations
//**************************************************************
//**************************************************************


//**************************************************************
// Members of regression
//**************************************************************
template<typename PPI,typename F>
typename mc::regression<PPI,F>::bmatrix 
	mc::regression<PPI,F>::Regression(const std::vector<bvector> & yVals, 
									 const std::vector<bvector> & factors, 
								     const fvector & testFunctions)
{
	//constructing the matrix Phi 
	bmatrix::size_type size1(factors.size()),size2(testFunctions.size());
	bmatrix Phi(size1,size2);
	bmatrix::size_type i,j;
	for(i=0; i<size1; ++i)
		for(j=0; j<size2; ++j)
		{
			Phi(i,j)=testFunctions[j](factors[i]);
		}

	//constructing the matrix yValsMatrix 
	bmatrix::size_type sizeY1(factors.size()),sizeY2(yVals[0].size());
	bmatrix yValsMatrix(sizeY1,sizeY2);
	bmatrix::size_type iY,jY;
	for(iY=0; iY<sizeY1; ++iY)
		for(jY=0; jY<sizeY2; ++jY)
		{
			yValsMatrix(iY,jY)=yVals[iY][jY];
		}


	//constructing A=Phi^T*Phi, B=Phi^T*yValsMatrix
	bmatrix PhiTr=trans(Phi);
	bmatrix A=prod(PhiTr,Phi);
	bmatrix B=prod(PhiTr,yValsMatrix);

	//solving linear equations Ax=B
	boost::numeric::ublas::lu_factorize(A);
	boost::numeric::ublas::lu_substitute<const bmatrix,bmatrix>(A,B);

	return B;
}

template<typename PPI,typename F>
mc::bvector & 
	mc::regression<PPI,F>::Projection(const mc::bvector & factor, 
			     				     const fvector & testFunctions, 
									 const bmatrix & coefficients,
									 mc::bvector & bvOut)
{
	bmatrix::size_type i,n; 
	n=std::min(testFunctions.size(), coefficients.size1());

	bvOut=boost::numeric::ublas::zero_vector<bvector::value_type>(coefficients.size2());
	for(i=0;i<n;++i)
	{
		const boost::numeric::ublas::matrix_row<const bmatrix> coeffI(coefficients,i);
		bvOut+=coeffI*testFunctions[i](factor);
	}
	return bvOut;
}
