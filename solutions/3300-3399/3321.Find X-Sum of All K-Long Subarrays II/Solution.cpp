// 题目：3321. 计算子数组的 x-sum II（Find X-Sum of All K-Long Subarrays II）
// 思路：滑动窗口 + 两个有序集合对顶。l 维护窗口内按 (出现次数, 值) 排序的前 x 个元素，r 存其余元素，s 维护 l 中 次数×值 的和；
// 每次滑动先把进出窗口的元素从结构中删除再按新次数加回，并把 l 的大小调回 x。时间复杂度：O(n log n)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> findXSum(vector<int>& nums, int k, int x) {  // nums：输入数组；k：窗口长度；x：每个窗口取前 x 个元素
        using pii = pair<int, int>;  // 集合里存 (出现次数, 元素值)，pair 的字典序比较正好就是题目要求的排序规则
        set<pii> l, r;  // l：贡献 x-sum 的前 x 大元素；r：被挤出的剩余元素
        long long s = 0;  // l 中所有元素的 次数×值 之和，也就是答案
        unordered_map<int, int> cnt;  // 窗口内每个元素值的出现次数
        auto add = [&](int v) {  // 把值 v 按它当前的 (次数, 值) 插入 l 或 r
            if (cnt[v] == 0) {  // 次数为 0 说明 v 不在窗口内
                return;  // 无需插入，直接返回
            }
            pii p = {cnt[v], v};  // 构造 (出现次数, 元素值) 二元组
            if (!l.empty() && p > *l.begin()) {  // 比 l 中最小元素还大，说明它应当进入前 x 大
                s += 1LL * p.first * p.second;  // 计入 x-sum（乘 1LL 防止 int 乘法溢出）
                l.insert(p);  // 放进 l
            } else {  // 比 l 的最小元素还小，先放进 r 备用
                r.insert(p);  // 否则先放进 r 备用
            }
        };
        auto remove = [&](int v) {  // 把值 v 当前的 (次数, 值) 从结构中删除
            if (cnt[v] == 0) {  // 次数为 0 说明集合里没有它
                return;  // 直接返回
            }
            pii p = {cnt[v], v};  // 用与插入时完全相同的二元组去查找
            auto it = l.find(p);  // 先看它是否在 l 中
            if (it != l.end()) {  // 在 l 中
                s -= 1LL * p.first * p.second;  // 从 x-sum 中扣掉它的贡献
                l.erase(it);  // 从 l 中删除
            } else {  // 不在 l 中，说明它一定在 r 中
                r.erase(p);  // 不在 l 就必然在 r，从 r 中删除
            }
        };
        vector<long long> ans;  // 每个长度为 k 的窗口的 x-sum
        for (int i = 0; i < nums.size(); ++i) {  // 右端点 i 逐个扩张窗口
            remove(nums[i]);  // 先删掉 nums[i] 旧的 (次数, 值)
            ++cnt[nums[i]];  // 窗口内 nums[i] 的出现次数 +1
            add(nums[i]);  // 再按新的次数重新插入

            int j = i - k + 1;  // 窗口左端点
            if (j < 0) {  // 窗口元素还不足 k 个
                continue;  // 先不统计答案
            }

            while (!r.empty() && l.size() < x) {  // l 不足 x 个时，从 r 中补进最大的元素
                pii p = *r.rbegin();  // r 中的最大元素（次数多、值大者优先）
                s += 1LL * p.first * p.second;  // 补进 x-sum
                r.erase(p);  // 从 r 中移除该元素
                l.insert(p);  // 加入 l
            }
            while (l.size() > x) {  // l 超过 x 个时，把最小的挤回 r
                pii p = *l.begin();  // l 中的最小元素
                s -= 1LL * p.first * p.second;  // 从 x-sum 中扣掉
                l.erase(p);  // 从 l 中删除
                r.insert(p);  // 放回 r
            }
            ans.push_back(s);  // 记录当前窗口的 x-sum

            remove(nums[j]);  // 左端点 nums[j] 即将滑出窗口，先移除它的旧二元组
            --cnt[nums[j]];  // 它的出现次数 -1
            add(nums[j]);  // 次数还不为 0 就按新次数插回结构
        }
        return ans;  // 返回所有窗口的答案
    }
};
