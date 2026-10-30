// 题目：3510. 移除最小数对使数组有序 II（Minimum Pair Removal to Sort Array II）
// 思路：用一张有序集合维护「每个相邻对的和 + 左端下标」，另一张有序集合维护仍存活的下标（代替双向链表）。同时统计当前相邻逆序对数量：每轮取出和最小的相邻对并合并，只更新被合并位置前后两个邻居的逆序对计数与相邻对记录，逆序对清零时即结束。
// 时间复杂度：O(n log n)，每个下标最多被合并一次，每次操作是若干次 O(log n) 的集合增删；空间复杂度：O(n)，两张集合各存 O(n) 条记录。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumPairRemoval(vector<int>& nums) {  // nums：待处理数组；返回使数组非递减所需的最少合并次数
        int n = nums.size();  // 数组长度
        int inv = 0;  // 当前相邻逆序对（nums[i] > nums[i+1]）的数量

        set<pair<long long, int>> sl;  // 按 (和, 左端下标) 升序的有序集合，首元素即和最小的相邻对
        set<int> idx;  // 仍存活的下标集合，用前驱/后继模拟双向链表
        vector<long long> arr(nums.begin(), nums.end());  // 元素用 long long 存，合并后的和可能超出 int

        for (int i = 0; i < n; ++i) idx.insert(i);  // 初始时所有下标都存活

        for (int i = 0; i < n - 1; ++i) {  // 预处理每一个相邻对
            if (nums[i] > nums[i + 1]) {  // 这一对构成逆序
                ++inv;  // 逆序对计数加一
            }  // 判定结束
            sl.insert({(long long) nums[i] + nums[i + 1], i});  // 把 (相邻和, 左端下标) 插入有序集合
        }  // 预处理结束

        int ans = 0;  // 记录已执行的合并次数
        while (inv > 0) {  // 还存在逆序对就继续合并
            ++ans;  // 合并次数加一

            auto it = sl.begin();  // 取出和最小的那个相邻对
            long long s = it->first;  // 该相邻对的和
            int i = it->second;  // 该相邻对的左端下标
            sl.erase(it);  // 这一对即将被合并，先把它从集合中删除

            auto j_it = idx.upper_bound(i);  // 右邻居就是比 i 大的第一个存活下标
            int j = *j_it;  // 取出右邻居下标（它会被合并掉）

            if (arr[i] > arr[j]) {  // 合并前 (i, j) 是逆序对
                --inv;  // 该逆序对随合并一起消失
            }  // 判定结束

            auto i_it = idx.find(i);  // 定位 i 在存活集合中的位置
            if (i_it != idx.begin()) {  // 存在左邻居 h 时才需要更新它
                auto h_it = prev(i_it);  // 前驱即左邻居
                int h = *h_it;  // 取出左邻居下标

                if (arr[h] > arr[i]) {  // 合并前 (h, i) 是逆序对
                    --inv;  // 该逆序对即将失效
                }  // 判定结束
                sl.erase({arr[h] + arr[i], h});  // 旧的相邻对 (h, i) 记录作废

                if (arr[h] > s) {  // 合并后这一对变成 (h, 新值 s)
                    ++inv;  // 新值变小，于是新增一个逆序对
                }  // 判定结束
                sl.insert({arr[h] + s, h});  // 登记新的相邻对和
            }  // 左邻居更新结束

            auto k_it = next(j_it);  // 右邻居的右邻居 k
            if (k_it != idx.end()) {  // 存在 k 时才需要更新
                int k = *k_it;  // 取出 k 的下标

                if (arr[j] > arr[k]) {  // 合并前 (j, k) 是逆序对
                    --inv;  // j 被删除，该逆序对消失
                }  // 判定结束
                sl.erase({arr[j] + arr[k], j});  // 旧的相邻对 (j, k) 记录作废

                if (s > arr[k]) {  // 合并后相邻对变成 (i, k)
                    ++inv;  // 新值变大，于是新增一个逆序对
                }  // 判定结束
                sl.insert({s + arr[k], i});  // 登记新的相邻对和，左端下标是 i
            }  // 右邻居更新结束

            arr[i] = s;  // 把合并后的和写回左端位置
            idx.erase(j);  // 右端下标被移除，相当于链表删除节点
        }  // 本轮合并结束

        return ans;  // 返回最少合并次数
    }  // 方法结束
};  // 类定义结束
