// a and m are coprime

typedef long long ll;

pair<ll, pair<ll, ll> > extendedEuclid(ll a, ll b)
{
    ll x = 1, y = 0;
    ll xLast = 0, yLast = 1;
    ll q, r, m, n;
    while(a!=0)
    {
        q = b/a;
        r = b%a;
        m = xLast - q*x;
        n = yLast - q*y;
        xLast = x, yLast = y;
        x = m, y = n;
        b = a, a = r;
    }
	return make_pair(b, make_pair(xLast, yLast));
}
ll modInverse(ll a, ll m)
{
	return (extendedEuclid(a, m).second.first + m)%m;
}
