vector<int> compute_Z(string s) {
  int n = s.length();
  vector<int> z(n, 0);
  z[0] = n;
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (r >= i) {
      z[i] = min(z[i - l], r - i + 1);
    }
    while (i+z[i] < n and s[i+z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}