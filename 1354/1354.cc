#include <cstdio>
#include <cstdlib>
#include <map>

typedef long long ll;
ll N, P, Q, X, Y;

ll solve(ll i, std::map<ll, ll> &context) {
  if (i <= 0)
    return 1;

  if (context[i]) {
    return context[i];
  }

  context[i] = solve(i / P - X, context) + solve(i / Q - Y, context);
  return context[i];
}

int main() {
  std::map<ll, ll> context;

  scanf("%lld %lld %lld %lld %lld", &N, &P, &Q, &X, &Y);
  printf("%lld\n", solve(N, context));
}
