// 3200. 三角形的最大高度（Maximum Height of a Triangle）
// 核心思路：三角形第 i 层需要 i 个同色球，颜色逐层交替；枚举底层颜色（红/蓝），按层号消耗对应颜色的球，能放下就继续，取两种起始颜色的最大高度。
// 复杂度：时间 O(√(red+blue))，空间 O(1)

class Solution {  // 定义题解类
public:  // 公开接口
    int maxHeightOfTriangle(int red, int blue) {  // 返回用红、蓝球交替堆叠能形成的最大三角形高度
        int ans = 0;  // 记录最大高度
        for (int k = 0; k < 2; ++k) {  // 枚举底层颜色：k = 0 用红球、k = 1 用蓝球
            int c[2] = {red, blue};  // 每轮重新拿到可用的红、蓝球数
            for (int i = 1, j = k; i <= c[j]; j ^= 1, ++i) {  // 尝试放第 i 层：颜色 j 逐层交替，当前颜色数量够放第 i 层才继续
                c[j] -= i;  // 当前层消耗 i 个该颜色的球
                ans = max(ans, i);  // 成功放下第 i 层，更新最大高度
            }  // 结束层数尝试
        }  // 结束起始颜色枚举
        return ans;  // 返回最大高度
    }  // 方法结束
};  // 类定义结束