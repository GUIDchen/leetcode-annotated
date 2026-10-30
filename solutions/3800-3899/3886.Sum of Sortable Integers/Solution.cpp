// 3886. 可排序整数求和 / Sum of Sortable Integers
// 核心思路：预处理前缀最大值、后缀最小值与相邻下降次数，判定分块后每块内最多一次下降且块内最大值不超过块后最小值；再枚举 n 的因子。
// 复杂度：时间 O(n + σ(n))（枚举因子并逐块扫描，σ(n) 为因子之和），空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有接口
    int sortableIntegers(vector<int>& nums) {  // 返回所有可排序块长度的和
        int n = nums.size();  // 数组长度
        vector<int> prefMax(n + 1);  // 前缀最大值数组
        for (int i = 0; i < n; ++i) {  // 从左到右预处理前缀最大值
            prefMax[i + 1] = max(prefMax[i], nums[i]);  // 前 i+1 个元素的最大值
        }  // 前缀最大值循环结束
        vector<int> suffMin(n + 1, 1000000000);  // 后缀最小值数组，末尾填大值哨兵
        for (int i = n - 1; i >= 0; --i) {  // 从右到左预处理后缀最小值
            suffMin[i] = min(nums[i], suffMin[i + 1]);  // 从 i 开始的后缀最小值
        }  // 后缀最小值循环结束
        vector<int> prefDrop(n);  // 前缀下降次数数组
        for (int i = 1; i < n; ++i) {  // 统计相邻元素的下降次数
            prefDrop[i] = prefDrop[i - 1] + (nums[i - 1] > nums[i]);  // 累计到当前位置的下降次数
        }  // 下降次数循环结束
        auto check = [&](int k) {  // 判断按长度 k 分块时每块是否都可排序
            for (int start = 0; start < n; start += k) {  // 逐块检查
                int end = start + k - 1;  // 当前块的最后下标
                int drops = prefDrop[end] - prefDrop[start];  // 块内相邻下降次数
                if (nums[end] > nums[start]) {  // 首尾顺序正常也按一次转折计入
                    ++drops;  // 把这次转折计入下降次数
                }  // 首尾判断结束
                if (drops > 1 || prefMax[start] > suffMin[start]) {  // 块内多次下降，或块内最大值超过块后最小值，则不可行
                    return false;  // 该分块方式不合法
                }  // 不合法判断结束
            }  // 逐块检查结束
            return true;  // 所有块都合法
        };  // check lambda 结束
        int ans = 0;  // 合法长度之和
        for (int i = 1; i <= n / i; ++i) {  // 枚举不超过 sqrt(n) 的因子
            if (n % i == 0) {  // i 是 n 的因子
                if (check(i)) {  // 检查长度 i 是否合法
                    ans += i;  // 累加合法长度
                }  // i 检查结束
                if (i != n / i && check(n / i)) {  // 检查互补因子，避免 i 与 n/i 相同时重复累加
                    ans += n / i;  // 累加互补长度
                }  // 互补因子判断结束
            }  // 因子判断结束
        }  // 因子枚举结束
        return ans;  // 返回合法长度总和
    }  // 方法结束
};  // 类定义结束
