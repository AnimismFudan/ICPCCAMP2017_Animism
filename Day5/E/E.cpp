#include <bits/stdc++.h>
using namespace std;

int Test, N, len, Q;

class rec{
	public:
	int t, x, r, n;
	bool ans;
} P[400010];

class hrec{
	public:
	int l, r, t;
	bool operator < (const hrec &X) const{
		return l + r < X.l + X.r;
	}
} h1, h2, h3;

set <hrec > H;
typedef set <hrec > :: iterator Hcp;
Hcp hc;

class trec{
	public:
	int t;
	Hcp l, r;
	bool operator < (const trec &X) const{
		if (t != X.t) return t < X.t;
		return (l -> l + l -> r) < ((X.l) -> l + (X.l) -> r);
	}
}t1, t2;

set <trec > T;

bool cmpt(const rec &A, const rec &B){
	if (A.t != B.t) return A.t < B.t;
	return A.n < B.n;
}

bool cmpn(const rec &A, const rec &B){
	return A.n < B.n;
}

bool inside(const hrec &A, int x, int t){
	if (A.l - (t - A.t) <= x && x <= A.r + (t - A.t)) return 1;
	return 0;
}

hrec mul(const hrec &A, const hrec &B, int t){
	hrec C;
	C.l = min(A.l - (t - A.t), B.l - (t - B.t));
	C.r = max(A.r + (t - A.t), B.r + (t - B.t));
	C.t = t;
	return C;
}

void T_Del(const Hcp &hcl, const Hcp & hcr){
	t2.t = (hcr->l - hcl->r + hcr->t + hcl->t + 1) / 2;
	t2.l = hcl;
	t2.r = hcr;
	T.erase(t2);
}

void T_Ins(const Hcp &hcl, const Hcp &hcr){
	t2.t = (hcr->l - hcl->r + hcr->t + hcl->t + 1) / 2;
	t2.l = hcl;
	t2.r = hcr;
	T.insert(t2);
}

void H_Del(const Hcp &hc){
	Hcp hcl;
	bool fl = 0, fr = 0;
	if (hc != H.begin()){
		hcl = hc;
		hcl--;
		fl = 1;
		T_Del(hcl, hc);
	}
	Hcp hcr = hc;
	hcr++;
	if (hcr != H.end()){
		fr = 1;
		T_Del(hc, hcr);
	}
	H.erase(hc);
	if (fl && fr)
		T_Ins(hcl, hcr);
}

void H_Ins(const hrec &h1){
	Hcp hcr = H.upper_bound(h1);
	Hcp hcl = hcr;
	bool fl = 0;
	bool fr = (hcr != H.end());
	if (hcl != H.begin()){
		hcl--;
		fl = 1;
	}
	if (fl && fr)
		T_Del(hcl, hcr);
	H.insert(h1);
	Hcp hc = H.find(h1);
	if (fl)
		T_Ins(hcl, hc);
	if (fr)
		T_Ins(hc, hcr);
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d", &Test);
	while (Test--){
		scanf("%d", &N);
		len = 0;
		for (int i = 1; i <= N; i++){
			++len;
			scanf("%d%d%d", &P[len].t, &P[len].x, &P[len].r);
			P[len].n = 0;
			P[len].ans = 0;
		}
		scanf("%d", &Q);
		for (int i = 1; i <= Q; i++){
			++len;
			scanf("%d%d", &P[len].t, &P[len].x);
			P[len].r = 0;
			P[len].n = i;
			P[len].ans = 0;
		}
		sort(P + 1, P + len + 1, cmpt);
		
		H.clear();
		T.clear();
		
		h1.l = 0; h1.r = 0; h1.t = 0;
		H.insert(h1);
		
		for (int i = 1; i <= len; i++){
/*			for (auto X : H)
				printf("%d %d %d\n", X.l, X.r, X.t);
			printf("----------\n");*/
			if (H.empty()) break;
			while (!T.empty()){
				t1 = *(T.begin());
				if (t1.t > P[i].t) break;
				h1 = mul(*(t1.l), *(t1.r), P[i].t);
				H_Del(t1.l);
				H_Del(t1.r);
				H_Ins(h1);
			}
			if (P[i].n == 0){
				h1.l = P[i].x - P[i].r + 1;
				h1.r = P[i].x - P[i].r + 1;
				hc = H.upper_bound(h1);
				h1.r = P[i].x + P[i].r - 1;
				if (hc != H.begin()){
					hc--;
					if (hc->r + (P[i].t - hc->t) < h1.l)
						hc++;
				}
				while (hc != H.end()){
					if ((hc->l) - (P[i].t - (hc->t)) > h1.r) break;
					Hcp hcnex = hc;
					hcnex++;
					h3 = (*hc);
					h3.l -= (P[i].t - h3.t);
					h3.r += (P[i].t - h3.t);
					h3.t = P[i].t;
					H_Del(hc);
					if (h3.l <= min(h3.r, h1.l - 1)){
						h2.l = h3.l;
						h2.r = min(h3.r, h1.l - 1);
						h2.t = h3.t;
						H_Ins(h2);
					}
					if (max(h3.l, h1.r + 1) <= h3.r){
						h2.l = max(h3.l, h1.r + 1);
						h2.r = h3.r;
						h2.t = h3.t;
						H_Ins(h2);
					}
					hc = hcnex;
				}
			}else{
				h1.l = P[i].x;
				h1.r = P[i].x;
				hc = H.upper_bound(h1);
				P[i].ans = 0;
				if (hc != H.end() && inside(*(hc), P[i].x, P[i].t))
					P[i].ans = 1;
				if (hc != H.begin()) hc--;
				if (hc != H.end() && inside(*(hc), P[i].x, P[i].t))
					P[i].ans = 1;
			}
		}
		sort(P + 1, P + len + 1, cmpn);
		for (int i = 1; i <= len; i++)
			if (P[i].n){
				P[i].ans ? printf("@") : printf("*");
			}
		printf("\n");
	}
}