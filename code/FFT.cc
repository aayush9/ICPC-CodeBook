template<typename fpt>
struct fft_wrap {
  using cpx_t = complex<fpt>;
  const fpt two_pi = 4 * acosl(0);

  vector<cpx_t> roots; //stores the N-th roots of unity.
  int N;

  fft_wrap(int N) : roots(N), N(N) {
    for (int i = 0; i < N; ++i) {
      roots[i] = EXP(two_pi * i / fpt(N));
    }
  }

  cpx_t EXP(fpt theta) {
    return {cos(theta), sin(theta)};
  }

  void fft(cpx_t *in, cpx_t *out, int size, int dir){
    bit_reverse(in, out, size);
    for (int s = 0; (1 << s) < size; ++s) {
      int s_ = s + 1;
      for (int k = 0; k < size; k += (1 << s_)) {
        for (int j = 0; j < (1 << s); ++j) {
          int id = (N + dir * (N >> s_) * j) & (N - 1);
          cpx_t w = roots[id];
          cpx_t t = w * out[k + j + (1 << s)];
          cpx_t u = out[k + j];
          out[k + j] = u + t;
          out[k + j + (1 << s)] = u - t;
        }
      }
    }
  }

  void bit_reverse(cpx_t *in, cpx_t *out, int size){
    for (int i = 0; i < size; ++i) {
      int rev = 0, i_copy = i;
      for (int j = 0; (1 << j) < size; ++j) {
        rev = (rev << 1) + (i_copy & 1);
        i_copy >>= 1;
      }
      out[rev] = in[i];
    }
  }
};

int main(){
  typedef complex<double> cpx_t;
  fft_wrap<double> fft_wrapper(2048);

  vector<cpx_t> in = {1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0}, out(8);

  fft_wrapper.fft(&in[0], &out[0], 8, 1);
  fft_wrapper.fft(&out[0], &in[0], 8, -1);
  for (int i = 0; i < 8; ++i) {
    cout << in[i].real() << ' ' << in[i].imag() << endl;
  }
}