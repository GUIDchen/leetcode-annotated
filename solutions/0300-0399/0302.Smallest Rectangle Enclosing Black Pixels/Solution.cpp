// 题目：302. 包含全部黑色像素的最小矩形（Smallest Rectangle Enclosing Black Pixels）
// 思路：把上下左右四条边界分别转成单调判定问题，在「含黑像素」的行/列区间上做二分查找。
// 时间复杂度：O(n log m + m log n)，每次判定扫描一行或一列；空间复杂度：O(1)，只用常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minArea(vector<vector<char>>& image, int x, int y) {  // image：0/1 字符矩阵；(x, y) 是任一黑像素坐标，返回包含全部黑像素的最小矩形面积
        int m = image.size(), n = image[0].size();  // 行数 m 与列数 n（题面保证矩阵非空，image[0] 一定有效）
        int left = 0, right = x;  // 上边界先在行区间 [0, x] 内二分：x 这一行必定含黑像素
        while (left < right) {  // 循环不变量：真正的上边界始终落在 [left, right] 中
            int mid = (left + right) >> 1;  // 取中点行，右移一位等价于整除 2
            int c = 0;  // 扫描这一行的列指针，从第 0 列开始
            while (c < n && image[mid][c] == '0') ++c;  // 跳过连续的白像素，直到遇到 '1' 或越界
            if (c < n)  // 若 c < n，说明这一行含有黑像素
                right = mid;  // 上边界可能是 mid 或更靠上，收缩右端
            else  // 否则这一行整行都是白像素
                left = mid + 1;  // 上边界必然在 mid 下方，把左端推到 mid+1
        }  // 二分收敛，left 即上边界
        int u = left;  // u 就是最上面的黑像素所在行
        left = x;  // 下一轮：在行区间 [x, m-1] 内二分下边界
        right = m - 1;  // 右端先取到最后一行
        while (left < right) {  // 这是「找最后一个满足条件的行」，需要向上取整的中点
            int mid = (left + right + 1) >> 1;  // 加 1 再右移：区间只剩两个元素时 mid 取到右侧，避免死循环
            int c = 0;  // 重新从第 0 列扫描 mid 这一行
            while (c < n && image[mid][c] == '0') ++c;  // 跳过白像素，找这一行里第一个 '1'
            if (c < n)  // 该行含黑像素
                left = mid;  // 下边界可能是 mid 或更靠下，保留左端 mid
            else  // 该行全白
                right = mid - 1;  // 下边界一定在 mid 之上
        }  // 循环结束，left 即下边界
        int d = left;  // d 是最下面的黑像素所在行
        left = 0;  // 第三轮：在列区间 [0, y] 内二分左边界
        right = y;  // 右端先取到 y 这一列
        while (left < right) {  // 换成按列判定的同一套二分框架
            int mid = (left + right) >> 1;  // 取中点列
            int r = 0;  // 扫描这一列的行指针，从第 0 行开始
            while (r < m && image[r][mid] == '0') ++r;  // 跳过这一列上方的白像素，直到遇到 '1'
            if (r < m)  // r < m 说明这一列存在黑像素
                right = mid;  // 左边界可能是 mid 或更靠左，收缩右端
            else  // 整列皆白
                left = mid + 1;  // 左边界在 mid 的右侧
        }  // 循环结束，left 即左边界
        int l = left;  // l 是最左边的黑像素所在列
        left = y;  // 最后一轮：在列区间 [y, n-1] 内二分右边界
        right = n - 1;  // 右端先取到最后一列
        while (left < right) {  // 「找最后一个满足条件的列」
            int mid = (left + right + 1) >> 1;  // 向上取整的中点列
            int r = 0;  // 重新从第 0 行扫描 mid 这一列
            while (r < m && image[r][mid] == '0') ++r;  // 跳过这一列的白像素
            if (r < m)  // 该列含黑像素
                left = mid;  // 右边界可能是 mid 或更靠右，保留左端 mid
            else  // 该列全白
                right = mid - 1;  // 右边界在 mid 的左侧
        }  // 循环结束，left 即右边界
        int r = left;  // r 是最右边的黑像素所在列
        return (d - u + 1) * (r - l + 1);  // 高度 (d-u+1) 乘宽度 (r-l+1)，即最小外接矩形面积
    }  // minArea 结束
};  // Solution 类结束