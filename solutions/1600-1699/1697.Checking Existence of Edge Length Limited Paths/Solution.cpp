// 题目：1697. 检查边长度限制的路径是否存在（Checking Existence of Edge Length Limited Paths）
// 思路：离线处理。边按长度升序、询问按 limit 升序，用并查集逐步把长度小于当前 limit 的边并入，再判断两端点是否连通。
// 时间复杂度：O((E + Q) log (E + Q))，排序为主，并查集近似常数；空间复杂度：O(n + E + Q)，存并查集、排序后的询问下标与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {  // n：点数；edgeList：无向边 [u, v, w]；queries：询问 [a, b, limit]
        vector<int> p(n);  // 并查集的父指针数组
        iota(p.begin(), p.end(), 0);  // 初始时每个点各自成集合，父指针指向自己
        sort(edgeList.begin(), edgeList.end(), [](auto& a, auto& b) { return a[2] < b[2]; });  // 边按长度升序，便于随 limit 增大逐条加入
        function<int(int)> find = [&](int x) -> int {  // 路径压缩的查找函数
            if (p[x] != x) p[x] = find(p[x]);  // 不是根就递归找根，并把路径上的点直接挂到根上
            return p[x];  // 返回根，即所属集合的代表元
        };
        int m = queries.size();  // 询问个数
        vector<bool> ans(m);  // 按原始询问下标保存答案
        vector<int> qid(m);  // 询问下标的排序序列
        iota(qid.begin(), qid.end(), 0);  // 初始化为 0..m-1
        sort(qid.begin(), qid.end(), [&](int i, int j) { return queries[i][2] < queries[j][2]; });  // 询问按 limit 升序，保证边只被加入一次
        int j = 0;  // 下一条待加入的边在 edgeList 中的下标
        for (int i : qid) {  // 按 limit 从小到大回答每个询问
            int a = queries[i][0], b = queries[i][1], limit = queries[i][2];  // 取出该询问的两端点和长度限制
            while (j < edgeList.size() && edgeList[j][2] < limit) {  // 把所有长度严格小于 limit 的边并入并查集
                int u = edgeList[j][0], v = edgeList[j][1];  // 取出该边的两个端点
                p[find(u)] = find(v);  // 合并两个端点所在的集合
                ++j;  // 该边处理完毕，指向下一条
            }
            ans[i] = find(a) == find(b);  // 根相同说明存在一条所有边都小于 limit 的路径
        }
        return ans;  // 返回按原始顺序排列的答案
    }
};