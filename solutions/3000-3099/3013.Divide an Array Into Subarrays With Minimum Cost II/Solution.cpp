// 题目：3013. 将数组分成最小总代价的子数组 II（Divide an Array Into Subarrays With Minimum Cost II）
// 思路：首元素固定计入代价，其余 k-1 个切点只能落在下标 1..dist+1 的滑动窗口内。用两个 multiset 维护窗口（l 存最小的 k-1 个数、r 存其余候选），窗口整体右移时左端删一个、右端加一个，再用两次平衡把 l 的大小修回 k-1，s 始终等于首元素加 l 之和。
// 时间复杂度：O(n log n)，每次窗口移动做常数次 multiset 操作；空间复杂度：O(dist)，两个多重集合合计保存窗口内的元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumCost(vector<int>& nums, int k, int dist) {  // nums：输入数组；k：要切成的子数组个数；dist：相邻两个切点下标之差的上限
        --k;  // 子数组个数 k 减 1，变成「除首元素外还需要挑的切点个数」
        multiset<int> l(nums.begin() + 1, nums.begin() + dist + 2), r;  // l 保存窗口 nums[1..dist+1] 中被选中的最小 k 个数；r 保存其余候选（两者都升序，multiset 允许重复值）
        long long s = accumulate(nums.begin(), nums.begin() + dist + 2, 0LL);  // s 是「首元素 + 窗口元素」的总和，先把整个窗口全加进来，稍后再剔除多余的大元素
        while (l.size() > k) {  // l 中元素超过 k 个，需要把最大的挪到 r，使 l 恰好留下最小的 k 个
            int x = *l.rbegin();  // rbegin() 指向 multiset 中的最大元素
            l.erase(l.find(x));  // 按迭代器删除单个元素：erase(值) 会删掉所有重复值，与只删一个的语义不符
            s -= x;  // 被挪走的元素不再计入总和
            r.insert(x);  // 放进右侧候选集合
        }  // 左侧裁剪完成，此时 s 就是第一个窗口的最小总代价
        long long ans = s;  // 第一个窗口的结果作为当前最优解
        for (int i = dist + 2; i < nums.size(); ++i) {  // 窗口右端点从 dist+2 开始滑动，i 是最新切点的下标，窗口覆盖 i-dist-1..i-1
            int x = nums[i - dist - 1];  // 即将滑出窗口左端的元素
            auto it = l.find(x);  // 先判断它是否在左侧被选中的集合里
            if (it != l.end()) {  // 在左侧：说明它此前被计入了 s
                l.erase(it);  // 从左侧删除该值的一个副本
                s -= x;  // 总和同步减去它
            } else {  // 不在左侧，说明它此前待在右侧候选集合里
                r.erase(r.find(x));  // 从右侧删除该值的一个副本
            }  // 分支结束，左端滑出的元素已经清理干净
            int y = nums[i];  // 从窗口右端新进入的元素
            if (y < *l.rbegin()) {  // 比左侧最大值还小，说明它应该被选中（数量失衡交给后面的循环修）
                l.insert(y);  // 放进左侧选中集合
                s += y;  // 计入总和
            } else {  // 否则它暂时不值得被选中
                r.insert(y);  // 放进右侧候选集合
            }  // 分支结束
            while (l.size() == k - 1) {  // 删掉左端元素后左侧可能只剩 k-1 个，从右侧补一个最小的进来
                int x = *r.begin();  // 右侧最小值正是剩余候选中最该被选中的那个
                r.erase(r.find(x));  // 从右侧删除
                l.insert(x);  // 放进左侧
                s += x;  // 计入总和
            }  // 左侧补齐结束
            while (l.size() == k + 1) {  // 若新加入的元素让左侧变成 k+1 个，就把最大的挤回右侧
                int x = *l.rbegin();  // 左侧最大值就是该被淘汰的那个
                l.erase(l.find(x));  // 从左侧删除
                s -= x;  // 从总和中减掉
                r.insert(x);  // 放回右侧候选集合
            }  // 左侧裁剪结束，l 的大小恢复成 k
            ans = min(ans, s);  // 用当前窗口的最小代价更新全局答案
        }  // 所有窗口枚举完毕
        return ans;  // 返回所有窗口中 s 的最小值
    }  // 方法结束
};  // 类定义结束
