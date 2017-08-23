#include <filter/vector_input.h>


//Force the compiler to generate a Real and a Complex version of VectorInput
template class VectorInput<Real>;
template class VectorInput<Complex>;


///\cond IMPLEMENTATION_DETAILS
template<>
VectorInput<Real>::VectorInput(uint32_t sample_rate) :
	Filter(sample_rate, { Filter::FilterOutputType::REAL })
{
}
///\endcond


///\cond IMPLEMENTATION_DETAILS
template<>
VectorInput<Complex>::VectorInput(uint32_t sample_rate) :
	Filter(sample_rate, { Filter::FilterOutputType::COMPLEX })
{
}
///\endcond


///\cond IMPLEMENTATION_DETAILS
template<>
VectorInput<Real>::VectorInput(uint32_t sample_rate, const std::vector<Real>& out) :
	Filter(sample_rate, { Filter::FilterOutputType::REAL }),
	output_samples(out)
{
}
///\endcond


///\cond IMPLEMENTATION_DETAILS
template<>
VectorInput<Complex>::VectorInput(uint32_t sample_rate, const std::vector<Complex>& out) :
	Filter(sample_rate, { Filter::FilterOutputType::COMPLEX }),
	output_samples(out)
{
}
///\endcond


///\cond IMPLEMENTATION_DETAILS
template<>
void VectorInput<Real>::Update()
{
	auto out = real();
	for (int i = 0; i < RealSimd::static_size; ++i) {
		out[i] = output_samples[current_sample];
		NextSample();
	}
}
///\endcond


///\cond IMPLEMENTATION_DETAILS
template<>
void VectorInput<Complex>::Update()
{
	auto out_re = real();
	auto out_im = imag();
	for (int i = 0; i < RealSimd::static_size; ++i) {
		out_re[i] = output_samples[current_sample].real();
		out_im[i] = output_samples[current_sample].imag();
		NextSample();
	}
}
///\endcond


template<typename Tout>
void VectorInput<Tout>::SetInput(const std::vector<Tout>& out)
{
	output_samples = out;
}