# Perlin-Noise
My implementation of Perlin Noise using SFML.

![image](https://user-images.githubusercontent.com/103447109/217922232-ef7684d7-d1aa-4323-bb9f-98a9e693a886.png)
Here is my implementation of the standard Perlin Noise algorithm. It is closely related to Wikipedia's definition of noise (https://en.wikipedia.org/wiki/Perlin_noise)
The interpolation function used for calculating the weights at each pixel was (x * (x * 6.0 - 15.0) + 10.0) * x * x * x, which produces a smooth gradient from x = 0 to x = 1

![image](https://user-images.githubusercontent.com/103447109/217922487-0e62bb14-ee90-43e3-bd4d-624b2acfee3e.png)
Here, I added an alpha value that allows you to choose the ratio of each color.

![image](https://user-images.githubusercontent.com/103447109/217922822-cea5245b-104c-4348-9c37-e55949076121.png)
Playing around with my own function based on a bell curve, I created a much bolder way of displaying the colors. The extreme values were replaced with yellow and red, while the less extreme values were magenta and blue.

![image](https://user-images.githubusercontent.com/103447109/217923930-3a2c37db-df83-47a2-afe0-604448d948e8.png)
Here is another effect I created while playing around with my algorithm.
