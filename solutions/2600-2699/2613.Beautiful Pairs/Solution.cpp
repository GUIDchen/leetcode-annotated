// 题目：2613. 美数对（Beautiful Pairs）
// 思路：先把每个点压成整数查重（重合点距离为 0 直接返回），再按 x 排序做分治「最近点对」：合并时用 |x - 中线x| <= 当前最优截出带状区域，按 y 排序后只比较 y 差不超过当前最优的对，并用下标字典序做平局裁决。
// 时间复杂度：O(n log^2 n)，每层递归都要对带状区域排序；空间复杂度：O(n)，用于哈希表、点集与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> beautifulPair(vector<int>& nums1, vector<int>& nums2) {  // nums1/nums2 分别给出点的横纵坐标；返回距离最小的两个下标
        int n = nums1.size();  // 点的个数
        unordered_map<long long, vector<int>> pl;  // 编码值 -> 出现过的下标列表，用来发现重合的点
        for (int i = 0; i < n; ++i) {  // 第一遍：按编码值把下标分组
            pl[f(nums1[i], nums2[i])].push_back(i);  // f 把二维坐标压成唯一整数，把当前下标挂到该编码上
        }  // 分组结束
        vector<tuple<int, int, int>> points;  // 分治用的点集，每个元素是 (x, y, 原始下标)
        for (int i = 0; i < n; ++i) {  // 第二遍：按原顺序扫描，顺带处理重合点
            long long z = f(nums1[i], nums2[i]);  // 当前点的编码值
            if (pl[z].size() > 1) {  // 同一坐标出现了不止一次，则最近距离必为 0（理论最小值）
                return {i, pl[z][1]};  // 直接返回当前下标与同坐标的第二个下标
            }  // 重合分支结束
            points.emplace_back(nums1[i], nums2[i], i);  // 没有重合点，把 (x, y, 下标) 放进点集
        }  // 建点集结束

        function<tuple<int, int, int>(int, int)> dfs = [&](int l, int r) -> tuple<int, int, int> {  // 分治函数：处理 points[l..r]，返回 (最小距离, 较小下标, 较大下标)
            if (l >= r) {  // 区间内不足两个点，最近距离视为无穷大
                return {1 << 30, -1, -1};  // 1 << 30 充当 INF，下标用 -1 表示无效
            }  // 递归出口结束
            int m = (l + r) >> 1;  // 取中点切分；右移一位等价于除以 2
            int x = get<0>(points[m]);  // 中线的横坐标，合并时用来截取带状区域
            auto t1 = dfs(l, m);  // 左半区间的最优解
            auto t2 = dfs(m + 1, r);  // 右半区间的最优解
            if (get<0>(t1) > get<0>(t2) || (get<0>(t1) == get<0>(t2) && (get<1>(t1) > get<1>(t2) || (get<1>(t1) == get<1>(t2) && get<2>(t1) > get<2>(t2))))) {  // 按 (距离, 较小下标, 较大下标) 的字典序挑出更优的一侧作为当前最优
                swap(t1, t2);  // 交换后让 t1 持有更优解
            }  // 择优结束
            vector<tuple<int, int, int>> t;  // 带状区域：与中线水平距离不超过当前最优的那些点
            for (int i = l; i <= r; ++i) {  // 遍历本区间所有点
                if (abs(get<0>(points[i]) - x) <= get<0>(t1)) {  // 只有横坐标足够靠近中线，才可能刷新最优距离
                    t.emplace_back(points[i]);  // 收集进带状区域
                }  // 筛选分支结束
            }  // 带状区域收集完毕
            sort(t.begin(), t.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {  // 带状区域按 y 升序排列，方便后面用 y 差剪枝
                return get<1>(a) < get<1>(b);  // tuple 第二项是 y，只按它比较
            });  // 排序结束
            for (int i = 0; i < t.size(); ++i) {  // 枚举带状区域中每个点作为配对的一端
                for (int j = i + 1; j < t.size(); ++j) {  // 只需向 y 更大的方向找另一端，避免重复
                    if (get<1>(t[j]) - get<1>(t[i]) > get<0>(t1)) {  // y 差已超过当前最优，序号更大的点只会更远
                        break;  // 直接跳出内层循环
                    }  // 剪枝分支结束
                    int pi = min(get<2>(t[i]), get<2>(t[j]));  // 统一成 (较小下标, 较大下标)，用于字典序比较
                    int pj = max(get<2>(t[i]), get<2>(t[j]));  // 另一个下标
                    int d = dist(get<0>(t[i]), get<1>(t[i]), get<0>(t[j]), get<1>(t[j]));  // 两点的曼哈顿距离
                    if (d < get<0>(t1) || (d == get<0>(t1) && (pi < get<1>(t1) || (pi == get<1>(t1) && pj < get<2>(t1))))) {  // 距离更小，或距离相同但下标对字典序更小，则更新最优
                        t1 = {d, pi, pj};  // 记录新的最优三元组
                    }  // 更新分支结束
                }  // 内层枚举结束
            }  // 外层枚举结束
            return t1;  // 返回本区间的最优解
        };  // lambda 定义结束

        sort(points.begin(), points.end());  // 按 (x, y, 下标) 排序，满足分治要求 x 有序
        auto [_, pi, pj] = dfs(0, points.size() - 1);  // 结构化解包，忽略距离本身，只取答案下标对
        return {pi, pj};  // 下标较小、较大的一对即题目要求的答案
    }  // 方法结束

    long long f(int x, int y) {  // 把 (x, y) 编码成一个整数用于判重
        return x * 100001LL + y;  // 坐标不超过 1e5，乘 100001 保证不同坐标编码不同
    }  // 编码函数结束

    int dist(int x1, int y1, int x2, int y2) {  // 曼哈顿距离
        return abs(x1 - x2) + abs(y1 - y2);  // 横纵坐标差的绝对值之和
    }  // 距离函数结束
};  // 题解类结束