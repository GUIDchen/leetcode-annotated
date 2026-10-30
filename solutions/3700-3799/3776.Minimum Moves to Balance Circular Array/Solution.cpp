// 3776. 使循环数组余额非负的最少移动次数 / Minimum Moves to Balance Circular Array
// 核心思路：总和为负直接无解；否则以余额最小的位置为缺口，由近及远从左右两侧搬运余额填坑，越近的搬运代价越小，贪心即可最优。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)，其中 n 为数组长度。
class Solution {  // 定义题解类
public:  // 公有成员
    long long minMoves(vector<int>& balance) {  // 返回使循环数组所有余额非负所需的最少移动次数
        long long sum = 0;  // 统计数组总和
        for (int b : balance) {  // 遍历每个位置的余额
            sum += b;  // 累加当前余额
        }  // 求和结束
        if (sum < 0) {  // 总和为负时，再怎么搬也无法让全部非负
            return -1;  // 判定为不可能
        }  // 判断结束

        int n = balance.size();  // 数组长度
        int mn = balance[0];  // 记录最小余额，先假定在 0 号位置
        int idx = 0;  // 记录最小余额的下标
        for (int i = 1; i < n; i++) {  // 从第二个元素开始寻找最小值
            if (balance[i] < mn) {  // 找到更小的余额
                mn = balance[i];  // 更新最小值
                idx = i;  // 更新最小值下标
            }  // 分支结束
        }  // 扫描结束

        if (mn >= 0) {  // 所有余额都已经非负
            return 0;  // 无需任何操作
        }  // 判断结束

        int need = -mn;  // 需要给缺口补充的额度
        long long ans = 0;  // 累计移动次数

        for (int j = 1; j < n; j++) {  // 从缺口两侧由近及远地搬运余额
            int a = balance[(idx - j + n) % n];  // 左侧距离 j 的位置
            int b = balance[(idx + j) % n];  // 右侧距离 j 的位置

            int c1 = min(a, need);  // 左侧最多能贡献的额度
            need -= c1;  // 扣减剩余需求
            ans += 1LL * c1 * j;  // 搬运 c1 次，每次花费 j

            int c2 = min(b, need);  // 右侧最多能贡献的额度
            need -= c2;  // 扣减剩余需求
            ans += 1LL * c2 * j;  // 搬运 c2 次，每次花费 j
        }  // 两侧扫完，移动次数确定

        return ans;  // 返回最少移动次数
    }  // 方法结束
};  // 类定义结束
