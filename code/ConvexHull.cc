typedef pair<long long, long long> PT;
long double dist(PT a, PT b){
  return sqrt(pow(a.first-b.first,2)+pow(a.second-b.second,2));
}

long long cross(PT o, PT a, PT b){
  PT OA = {a.first-o.first,a.second-o.second};
  PT OB = {b.first-o.first,b.second-o.second};
  return OA.first*OB.second - OA.second*OB.first;
}
vector<PT> convexhull(){
  vector<PT> hull;
  sort(a,a+n,[](PT i, PT j){
    if(i.second!=j.second)
      return i.second < j.second;
    return i.first < j.first;
  });
  for(int i=0;i<n;++i){
    while(hull.size()>1 && cross(hull[hull.size()-2],hull.back(),a[i])<=0)
      hull.pop_back();
    hull.push_back(a[i]);
  }
  for(int i=n-1, siz = hull.size();i--;){
    while(hull.size()>siz && cross(hull[hull.size()-2],hull.back(),a[i])<=0)
      hull.pop_back();
    hull.push_back(a[i]);
  }
  return hull;
}