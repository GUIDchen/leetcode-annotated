// 3618. Split Array by Prime Indices / 根据质数下标分割数组
// 核心思路：先用埃氏筛预处理质数表，再按下标是否为质数给元素赋正负号求和，最后取绝对值。
// 复杂度：筛法预处理 O(M log log M) 且只做一次，单次查询 O(n)；空间复杂度 O(M)。
const int M = 1e5 + 10;  // 质数表上界，略大于数组可能的最大长度
bool primes[M];  // primes[i] 表示下标 i 是否为质数
auto init = [] {  // 立即执行 Lambda：在程序启动时一次性完成筛法预处理
    memset(primes, true, sizeof(primes));  // 先把整张表全部置为 true
    primes[0] = primes[1] = false;  // 0 和 1 不是质数
    for (int i = 2; i < M; ++i) {  // 从 2 开始枚举
        if (primes[i]) {  // 只有质数才需要筛掉它的倍数
            for (int j = i + i; j < M; j += i) {  // 从 i 的两倍开始标记合数
                primes[j] = false;  // 标记为非质数
            }  // 结束倍数标记
        }  // 结束质数判断
    }  // 结束枚举
    return 0;  // Lambda 需要一个返回值来完成初始化
}();  // 立即调用，完成全局预处理

class Solution {  // 定义题解类
public:  // 公有成员：对外提供 splitArray
    long long splitArray(vector<int>& nums) {  // 按下标是否为质数分组求和后返回两组的绝对差
        long long ans = 0;  // ans 累积质数下标元素之和减去非质数下标元素之和
        for (int i = 0; i < nums.size(); ++i) {  // 逐个下标扫描
            ans += primes[i] ? nums[i] : -nums[i];  // 质数下标取正，否则取负
        }  // 结束遍历
        return abs(ans);  // 取绝对值得到两组之和的差
    }  // 方法结束
};  // 类定义结束