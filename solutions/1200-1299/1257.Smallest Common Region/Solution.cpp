// 题目：1257. 最小公共区域（Smallest Common Region）
// 思路：区域树里每个节点只有一个父区域，先用哈希表建出「子区域 → 父区域」的映射；把 region1 到根的整条祖先链放进哈希集合，再让 region2 沿父指针往上爬，第一个落进集合的节点就是最小公共祖先。
// 时间复杂度：O(L)，L 为所有区域名字的总数（建图）加上两条链的长度；空间复杂度：O(L)，需要存父子映射与祖先集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {  // regions：每个列表首元素是父区域、其余是它的子区域；region1/region2：待求公共区域的两个区域
        unordered_map<string, string> g;  // g 建立「子区域 → 父区域」映射，每个区域至多一个父区域
        for (const auto& r : regions) {  // 逐条解析层级信息
            string x = r[0];  // 每组第一个名字是父区域
            for (size_t i = 1; i < r.size(); ++i) {  // 从下标 1 开始都是它的直接子区域
                g[r[i]] = x;  // 记录子区域到父区域的边
            }
        }
        unordered_set<string> s;  // s 用来存放 region1 到根路径上的所有区域
        for (string x = region1; !x.empty(); x = g[x]) {  // 从 region1 出发沿父指针一路向上；x 为空串说明已经越过根、没有父区域了
            s.insert(x);  // 把当前区域记入集合（unordered_map 的 operator[] 会在缺失时插入空串，正好当作「无父」）
        }
        string x = region2;  // 换从 region2 出发向上寻找
        while (!g[x].empty() && s.find(x) == s.end()) {  // 只要还有父区域、且当前区域尚未命中 region1 的祖先链，就继续上爬
            x = g[x];  // 上移一层
        }
        return x;  // 停下时所在的区域即最小公共区域（可能是 region2 本身或其某个祖先）
    }
};
