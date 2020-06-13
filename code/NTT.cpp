// gen should be 5^((p - 1) / fft_wrapper_size)

template<int P>
struct field_t { ... };

template<typename fpt, int gen>
struct fft_wrap {
  vector<fpt> roots; //stores the N-th roots of unity.
  int N;
  fft_wrap(int _N) : roots(_N), N(_N) {
    roots[0] = 1;
    for (int i = 1; i < N; ++i) {
      roots[i] = roots[i - 1] * gen;
      if (i != N - 1) {
        assert(roots[i].v != 1);
      }
    }
  }
  void fft(fpt *in, fpt *out, int size, int dir) {
    bit_reverse(in, out, size);
    for (int s = 0; (1 << s) < size; ++s) {
      int s_ = s + 1;
      for (int k = 0; k < size; k += (1 << s_)) {
        for (int j = 0; j < (1 << s); ++j) {
          int id = (N + dir * (N >> s_) * j) & (N - 1);
          fpt w = roots[id];
          fpt t = w * out[k + j + (1 << s)];
          fpt u = out[k + j];
          out[k + j] = u + t;
          out[k + j + (1 << s)] = u - t;
        }
      }
    }
  }
  void bit_reverse(fpt *in, fpt *out, int size) {
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

using fpt = field_t<mod>;
fft_wrap<fpt, gen> fft_wrapper(1 << 18);

vector<fpt> polymul(vector<fpt> P1, vector<fpt> P2) {
  int fsize = P1.size() + P2.size() - 1;
  int N = max(P1.size(), P2.size());
  while(N & (N - 1)) {
    ++N;
  }
  N *= 2;
  P1.resize(N); P2.resize(N);
  vector<fpt> temp(N);
  fft_wrapper.fft(&P1[0], &temp[0], N, 1);
  fft_wrapper.fft(&P2[0], &P1[0], N, 1);
  for (int i = 0; i < N; ++i) {
    P1[i] *= temp[i];
  }
  fft_wrapper.fft(&P1[0], &temp[0], N, -1);
  field_t<mod> inv(N);
  inv = inv.modexp(mod - 2);
  for (int i = 0; i < N; ++i) {
    temp[i] *= inv;
  }
  temp.resize(fsize);
  return temp;
}