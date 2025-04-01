struct segment_tree{
	int N;
	vector<int> tree;
	segment_tree(int N) : N(N){
		tree.resize(2 * N);
	}
	segment_tree(vector<int>& A){
		N = (int) A.size();
		tree.resize(2 * N);
		build(A, 1, 0, N - 1);
	}
	auto& operator[](size_t i) { return tree[i]; } // this funciton works for get element int this position
	
	// O (n)
	void build(vector<int>& values, int node, int l, int r){
		// if l and r are equal both are leaf node
		// left node = [l, m]
		// m = (l + r) / 2
		// left and right are nodes
		// left interval = [l, m], right intervla = [m + 1, r]
		// after complete fill nodes of left and right, we need to fill the [l, r] node
		if(l == r){
			tree[node] = values[l];
			dbg(l, r, node, tree[node]);
			return;
		}
		int m = (l + r) >> 1;
		int left = node + 1;
		int right = node + 2 * (m - l + 1);
		build(values, left, l, m);
		build(values, right, m + 1, r);
		tree[node] = tree[left] + tree[right];
		dbg(l, r, node, tree[node]);
	}
	
	// O (log N)
	void modify(int pos, int value, int node,  int l,  int r){
		// if l and r are equal, we found our node and update it
		if(l == r){
			tree[node] = value;
			return;
		}
		int m = (l + r) >> 1; // we get the mid
		int left = node + 1;
		int right = node + 2 * (m - l + 1);
		if(pos <= m) modify(pos, value, left, l, m);
		else modify(pos, value, right, m + 1, r);
		tree[node] = tree[left] + tree[right];
	}
	// O( c * log N)
	int query(int ql, int qr, int node, int l, int r){
		if(r < ql || l > qr) return 0;
		if(ql <= l && r <= qr) return tree[node];
		int m = (l + r) >> 1;
		int left = node + 1;
		int right = node + 2 * (m - l + 1);
		int ansL = query(ql, qr, left, l, m);
		int ansR = query(ql, qr, right, m + 1, r);
		return ansL + ansR;
	}

};

void GA(){
	vector<int> A = {2, 3, 1, 7, 5, 8, 3, 2, 5, 1};
	int n = 10;

	segment_tree st(A);
	cout << st.query(1, 5, 1, 0, n - 1) << '\n';
	st.modify(3, 10, 1, 0, n - 1);
	cout << st.query(1, 5, 1, 0, n - 1) << '\n';
	cout << st[1] << '\n';
}

int main(){
	cpu();
	int t = 1;
	//cin >> t;
	while (t--)
	{
		GA();
	}
	return 0;
}
