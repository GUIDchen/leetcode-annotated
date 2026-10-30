// 题目：4032. 至多 K 个不同质因数集合的最长子数组 / Longest Subarray With at Most K Distinct Prime Factors
// 核心思路：先用埃氏筛预处理 1e5 以内每个数的全部不同质因数，再用滑动窗口配哈希表维护窗口内不同质因数的个数
// 复杂度：时间复杂度 O(MX log log MX + n·ω(max))，空间复杂度 O(MX log log MX)
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    int longestSubarray(vector<int>& nums, int k) {  // 返回至多包含 k 个不同质因数的最长子数组长度
        const int MX = 100001;  // 预处理上界，题目保证 nums[i] <= 100000

        static vector<vector<int>> primes(MX);  // primes[x] 保存 x 的所有不同质因数，使用静态数组只预处理一次

        static bool initialized = false;  // 标记是否已完成一次性预处理
        if (!initialized) {  // 第一次调用时才做筛法预处理
            initialized = true;  // 置位标记，避免重复计算

            for (int i = 2; i < MX; i++) {  // 枚举每个可能的质因数候选
                if (primes[i].empty()) {  // primes[i] 为空说明 i 是质数（没有被更小的质数登记过）
                    for (int j = i; j < MX; j += i) {  // 把质数 i 登记到它的所有倍数上（埃氏筛思想）
                        primes[j].push_back(i);  // j 含有质因数 i，记录下来
                    }  // 结束倍数枚举
                }  // 结束质数判定
            }  // 结束质因数筛法
        }  // 结束一次性预处理

        unordered_map<int, int> cnt;  // cnt[p] 记录窗口内质因数 p 的出现次数

        int ans = 0;  // 答案：最长合法子数组长度
        int l = 0;  // 滑动窗口左端点

        for (int r = 0; r < nums.size(); r++) {  // 右端点从左到右扩张窗口
            for (int p : primes[nums[r]]) {  // 把新纳入的 nums[r] 的质因数全部计入窗口
                cnt[p]++;  // 质因数 p 的计数加一
            }  // 结束新元素的质因数登记

            while (cnt.size() > k) {  // 窗口内不同质因数超过 k 个时收缩左端点
                for (int p : primes[nums[l]]) {  // 扣除即将移出窗口的 nums[l] 的质因数
                    if (--cnt[p] == 0) {  // 计数减一后为 0 说明该质因数已不在窗口中
                        cnt.erase(p);  // 从哈希表删除，保证 size() 等于不同质因数个数
                    }  // 结束单次计数判断
                }  // 结束移出元素的质因数扣除
                l++;  // 左端点右移
            }  // 结束收缩循环

            ans = max(ans, r - l + 1);  // 用当前合法窗口长度更新答案
        }  // 结束右端点枚举

        return ans;  // 返回最长子数组长度
    }  // 结束方法
};  // 结束类定义