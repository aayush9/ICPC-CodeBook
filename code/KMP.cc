vector<int> find_prefix(const vector<int> &P){
  int M = P.size();
  vector<int> pi(M);
  /* pi[i] <- largest prefix P[0..pi[i]] which is a suffix of P[0..i]
   * (but not equal to it) */
  pi[0] = -1;
  for (int i = 1, k = -1; i < M; ++i) {
    while(k > -1 && P[k + 1] != P[i])
      k = pi[k];
    if (P[k + 1] == P[i]) ++k;
    pi[i] = k;
  } 
  return pi;
}
int kmp_matcher(const vector<int> &T, const vector<int> &P){
  int M = P.size(), N = T.size();
  vector<int> pi = find_prefix(P);
  int q = -1, matches = 0;
  for (int i = 0; i < N; ++i) {
    while(q > -1 && P[q + 1] != T[i])
      q = pi[q];
    if (P[q + 1] == T[i]) ++q;
    if (q == M - 1)
      ++matches, q = pi[q];
  }
  return matches;
}