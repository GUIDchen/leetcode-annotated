// 题目：2975. 移除栅栏得到的正方形田地的最大面积（Maximum Square Area by Removing Fences From a Field）
// 思路：把边界 1 与 m（n）也当成栅栏，枚举两两栅栏的距离得到横向、纵向的距离集合，正方形边长必须同时出现在两个集合里，取最大边长 d 后答案为 d*d。
// 时间复杂度：O((H+V)log(H+V) + H^2 + V^2)，排序加枚举间距；空间复杂度：O(H^2 + V^2)，两个去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {  // m：横向总长；n：纵向总长；hFences/vFences：可移除的栅栏位置坐标
        auto f = [](vector<int>& nums, int k) {  // 局部 lambda：把边界 k 与 1 也当成栅栏，返回所有间距组成的集合（间距即可能的边长）
            nums.push_back(k);  // 把上（右）边界 k 加入位置列表
            nums.push_back(1);  // 把下（左）边界 1 加入位置列表
            sort(nums.begin(), nums.end());  // 排序后任意两栅栏的差值就是一段可用长度
            unordered_set<int> s;  // 存放该方向上所有可能的间距，set 自动去重
            for (int i = 0; i < nums.size(); ++i) {  // 枚举较大的位置 i
                for (int j = 0; j < i; ++j) {  // 只枚举比 i 小的位置 j，保证差值为正且不重复配对
                    s.insert(nums[i] - nums[j]);  // 把 nums[i]-nums[j] 作为候选边长插入集合
                }  // 内层 j 循环结束
            }  // 外层 i 循环结束，所有栅栏配对都已枚举
            return s;  // 返回该方向全部候选边长
        };  // lambda 定义结束
        auto hs = f(hFences, m);  // 横向所有可能的边长
        auto vs = f(vFences, n);  // 纵向所有可能的边长
        int ans = 0;  // 记录横纵共有的最大边长，正方形要求横纵边长相等
        for (int h : hs) {  // 遍历横向候选边长 h
            if (vs.count(h)) {  // 若纵向也能取到 h，就说明能围出边长 h 的正方形
                ans = max(ans, h);  // 更新最大边长
            }  // if 分支结束
        }  // for 循环结束
        const int mod = 1e9 + 7;  // 题目要求对 1e9+7 取模
        return ans > 0 ? 1LL * ans * ans % mod : -1;  // 有合法边长则返回 d*d 取模；用 1LL 先把乘法提升到 64 位防溢出；没有则返回 -1
    }  // 方法结束
};  // 类定义结束