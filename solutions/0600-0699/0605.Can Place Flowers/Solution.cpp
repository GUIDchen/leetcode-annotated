// 题目：605. 种花问题（Can Place Flowers）
// 思路：从左到右贪心扫描，只要左侧、自身、右侧三个位置都为 0 就种一朵花，并原地修改避免相邻冲突。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只在原数组上就地修改。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {  // flowerbed 是 0/1 花坛，n 是还想种下的花朵数量
        int m = flowerbed.size();  // 花坛长度，作为扫描边界
        for (int i = 0; i < m; ++i) {  // 从左往右逐格判断能否种花
            int l = i == 0 ? 0 : flowerbed[i - 1];  // 左邻居；第一格左边越界，按空地 0 处理
            int r = i == m - 1 ? 0 : flowerbed[i + 1];  // 右邻居；最后一格右边越界，同样按空地 0 处理
            if (l + flowerbed[i] + r == 0) {  // 左、中、右三者都为 0 才满足不能相邻的规则
                flowerbed[i] = 1;  // 就地种下这朵花，后面的判断自然会把它当障碍
                --n;  // 待种数量减一
            }  // 可行性判断结束
        }  // 遍历结束
        return n <= 0;  // 待种数量已经减到 0 或更小，说明能全部种下
    }  // 方法结束
};  // 类定义结束