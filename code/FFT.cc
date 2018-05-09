// Source: My (forked) ICPC codebook: https://github.com/aayush9/ICPC-CodeBook/blob/master/code/FFT.cc
namespace FFT{
  vector<complex<long double>> A;
  int n,L;
  int ReverseBits(int k){
    int ret = 0;
    for(int i=0;i++<L;k/=2)
      ret = (ret<<1)|(k&1);
    return ret;
  }
  void BitReverseCopy(vector<complex<long double>> a){
    for (n=1,L=0;n<a.size();n<<=1,L++);
    A.resize(n);
    for (int k = 0; k < n; k++) 
      A[ReverseBits(k)] = a[k];
  }
  vector<complex<long double>> DFT(vector<complex<long double>> a, bool inverse) {
    BitReverseCopy(a);
    for (int s = 1; s <= L; s++) {
      int m = 1 << s;
      complex<long double> wm = exp(complex<long double>(0, 2.0 * M_PI / m));
      if (inverse) wm = complex<long double>(1, 0) / wm;
      for (int k = 0; k < n; k += m) {
        complex<long double> w = 1;
        for (int j = 0; j < m/2; j++) {
          complex<long double> t = w * A[k + j + m/2];
          complex<long double> u = A[k + j];
          A[k + j] = u + t;
          A[k + j + m/2] = u - t;
          w = w * wm;
        }
      }
      }
      if (inverse) for (int i = 0; i < n; i++) A[i] /= n;
      return A;
  }

  vector<long double> Convolution(vector<long double> a,vector<long double> b) {
    int L = 1;
    while ((1 << L) < a.size()) L++;
    while ((1 << L) < b.size()) L++;
    int n = 1 << (L+1);

    vector<complex<long double>> aa, bb;
    for (size_t i = 0; i < n; i++) aa.push_back(i < a.size() ? complex<long double>(a[i], 0) : 0);
    for (size_t i = 0; i < n; i++) bb.push_back(i < b.size() ? complex<long double>(b[i], 0) : 0);

    vector<complex<long double>> AA = DFT(aa, false);
    vector<complex<long double>> BB = DFT(bb, false);
    vector<complex<long double>> CC;
    for (size_t i = 0; i < AA.size(); i++) CC.push_back(AA[i] * BB[i]);
    vector<complex<long double>> cc = DFT(CC, true);
    vector<long double> c;
    for (int i=0;i<a.size()+b.size()-1;++i)
      c.push_back(cc[i].real());
    return c;
  }
}