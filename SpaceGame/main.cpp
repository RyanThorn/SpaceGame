
// includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <algorithm>
#include <math.h>

#include <list>

#include "GameObject.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Comet.h"
#include "Explosion.h"
#include "Background.h"
#include "Globals.h"

// Globals for main
bool keys[] = { false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE };
const int TOTAL_SPAWNS = 807;
//const int TOTAL_SPAWNS = 1415;
float spawnTimes[TOTAL_SPAWNS] = { 0.91, 0.95, 0.99, 1.04, 1.08, 1.10, 14.57, 14.62, 14.74, 14.77, 15.03, 15.06, 15.10, 15.19, 22.07, 22.11, 22.15, 22.24, 29.13, 29.19, 29.21, 29.23, 29.54, 29.57, 29.61, 30.01, 30.02, 30.03, 30.07, 30.46, 30.53, 30.90, 31.34, 31.79, 31.85, 32.23, 32.61, 32.65, 32.76, 33.10, 33.54, 33.61, 33.98, 33.99, 34.07, 34.42, 34.43, 34.52, 34.82, 34.83, 34.86, 35.27, 35.30, 35.31, 35.40, 35.75, 35.85, 35.96, 35.99, 36.19, 36.26, 36.63, 36.73, 37.07, 37.14, 37.51, 37.95, 38.39, 38.46, 38.49, 38.84, 39.27, 39.71, 39.81, 40.16, 40.62, 40.69, 41.04, 41.48, 41.51, 41.92, 41.99, 42.35, 42.43, 42.45, 42.80, 42.87, 43.04, 43.09, 43.24, 43.68, 43.76, 44.12, 44.56, 44.66, 45.00, 45.01, 45.10, 45.45, 45.89, 45.98, 46.32, 46.42, 46.72, 46.73, 46.77, 47.21, 47.65, 48.09, 48.53, 48.97, 49.42, 49.85, 49.95, 50.07, 50.08, 50.13, 50.30, 50.31, 50.73, 50.83, 51.14, 51.17, 51.62, 52.05, 52.50, 52.59, 52.94, 53.03, 53.38, 53.77, 53.82, 54.26, 54.71, 55.14, 55.24, 55.59, 56.02, 56.46, 56.56, 56.91, 57.00, 57.12, 57.35, 57.44, 57.79, 58.23, 58.32, 58.67, 59.11, 59.55, 59.65, 60.00, 60.44, 60.83, 60.84, 60.87, 61.31, 61.39, 61.75, 61.83, 62.20, 62.64, 63.07, 63.17, 63.52, 63.59, 63.97, 63.98, 64.19, 64.20, 64.41, 64.85, 65.28, 65.73, 65.74, 65.80, 66.17, 66.61, 66.70, 67.01, 67.04, 67.48, 67.58, 67.93, 68.00, 68.38, 68.82, 69.25, 69.35, 69.69, 70.14, 70.23, 70.57, 71.02, 71.23, 71.31, 71.46, 71.90, 71.99, 72.33, 72.39, 72.41, 72.43, 72.78, 72.87, 73.19, 73.22, 73.31, 73.66, 73.66, 74.10, 74.55, 74.56, 74.58, 74.95, 74.98, 75.39, 75.42, 75.86, 76.30, 76.71, 76.74, 76.80, 76.82, 76.84, 77.18, 77.63, 77.70, 78.06, 78.29, 78.32, 78.36, 78.52, 78.58, 78.95, 79.04, 79.40, 79.44, 79.47, 79.83, 80.27, 80.71, 80.78, 81.15, 81.21, 81.23, 81.60, 81.67, 82.04, 82.06, 82.48, 82.53, 82.55, 82.92, 82.92, 83.37, 83.38, 83.41, 83.43, 83.81, 83.87, 84.06, 84.09, 84.12, 84.26, 84.28, 84.30, 84.32, 84.50, 84.70, 84.94, 84.98, 85.00, 85.14, 85.16, 85.18, 85.20, 85.37, 85.38, 85.40, 85.42, 85.56, 85.61, 92.60, 92.62, 92.65, 92.77, 94.36, 94.39, 94.41, 94.50, 94.54, 94.56, 95.05, 95.08, 95.20, 95.23, 95.71, 95.74, 95.76, 95.78, 95.86, 96.15, 96.18, 96.20, 96.22, 96.30, 99.66, 99.76, 99.84, 113.35, 113.38, 113.41, 113.50, 113.55, 113.58, 113.59, 113.63, 113.77, 113.81, 113.83, 113.86, 113.87, 120.81, 120.81, 120.86, 120.89, 120.97, 120.98, 127.43, 127.46, 127.50, 127.58, 127.64, 127.72, 127.86, 127.91, 149.03, 149.06, 149.12, 149.48, 149.51, 149.93, 149.97, 150.36, 150.39, 150.43, 150.80, 150.81, 150.83, 150.85, 150.87, 151.25, 151.27, 151.67, 151.69, 152.12, 152.14, 152.15, 152.17, 152.52, 152.56, 152.58, 152.99, 153.07, 153.39, 153.44, 153.47, 153.49, 153.51, 153.88, 153.93, 154.33, 154.34, 154.41, 154.43, 154.78, 154.80, 155.17, 155.21, 155.65, 155.70, 155.87, 156.10, 156.11, 156.16, 156.53, 156.58, 156.97, 157.00, 157.02, 157.04, 157.41, 157.86, 157.92, 158.31, 158.74, 158.75, 158.78, 159.18, 159.19, 159.22, 159.24, 159.62, 159.66, 159.68, 160.06, 160.07, 160.50, 160.57, 160.94, 161.01, 161.38, 161.39, 161.41, 161.82, 161.85, 161.87, 162.26, 162.26, 162.31, 162.70, 162.75, 162.92, 162.94, 162.95, 162.97, 162.99, 163.16, 163.17, 163.60, 163.63, 163.65, 164.04, 164.06, 164.07, 164.47, 164.48, 164.91, 164.97, 165.35, 165.79, 166.23, 166.28, 166.67, 166.74, 167.11, 167.16, 167.18, 167.56, 167.98, 168.04, 168.45, 168.88, 168.92, 169.32, 169.76, 169.79, 169.97, 169.99, 170.02, 170.20, 170.21, 170.23, 170.25, 170.27, 170.29, 170.63, 170.65, 170.71, 171.08, 171.09, 171.11, 171.13, 171.52, 171.96, 172.40, 172.41, 172.85, 172.86, 172.87, 173.29, 173.34, 173.35, 173.38, 173.73, 173.79, 174.17, 174.20, 174.21, 174.60, 174.61, 174.68, 175.08, 175.10, 175.12, 175.14, 175.49, 175.50, 175.93, 175.96, 175.98, 176.00, 176.38, 176.42, 177.10, 177.29, 177.30, 177.70, 177.74, 178.15, 178.16, 178.18, 178.61, 178.63, 178.64, 179.02, 179.08, 179.11, 179.46, 179.47, 179.49, 179.90, 180.33, 180.39, 180.78, 180.85, 181.24, 181.66, 181.73, 182.12, 182.55, 182.57, 182.98, 183.03, 183.42, 183.44, 183.47, 183.50, 183.52, 183.54, 183.90, 183.93, 184.10, 184.13, 184.16, 184.32, 184.34, 184.78, 184.82, 185.15, 185.19, 185.20, 185.22, 185.24, 185.26, 185.63, 185.70, 186.07, 186.12, 186.14, 186.51, 186.53, 186.58, 186.96, 186.98, 187.43, 187.82, 187.88, 188.28, 188.31, 188.32, 188.72, 188.77, 188.79, 189.16, 189.17, 189.60, 189.65, 189.69, 189.71, 189.85, 189.87, 189.89, 190.05, 190.29, 190.33, 190.75, 190.77, 190.94, 191.18, 191.21, 191.38, 191.39, 191.85, 191.87, 191.90, 192.26, 192.70, 192.75, 193.14, 193.15, 193.58, 194.01, 194.02, 194.04, 194.07, 194.48, 194.50, 194.82, 194.89, 194.90, 194.92, 194.94, 194.96, 194.98, 195.32, 195.36, 195.38, 195.40, 195.79, 196.21, 196.23, 196.65, 196.70, 196.72, 196.74, 196.76, 197.11, 197.14, 197.54, 197.99, 198.04, 198.19, 198.43, 198.45, 198.47, 198.49, 198.87, 198.89, 199.31, 199.37, 199.74, 199.79, 199.81, 200.18, 200.19, 200.25, 200.62, 200.65, 200.67, 201.06, 201.13, 201.50, 201.55, 201.96, 201.97, 202.01, 202.39, 202.43, 202.45, 202.83, 202.86, 202.88, 202.90, 203.27, 203.30, 203.31, 203.72, 203.82, 203.84, 204.15, 204.18, 204.22, 204.59, 205.03, 205.25, 205.49, 205.52, 205.54, 205.91, 205.93, 206.35, 206.38, 206.40, 206.42, 206.79, 206.81, 206.87, 207.24, 207.30, 207.67, 208.12, 208.17, 208.56, 209.00, 209.01, 209.05, 209.07, 209.44, 209.53, 209.90, 209.95, 210.34, 210.39, 210.78, 210.79, 210.81, 210.83, 211.20, 211.22, 211.25, 211.27, 211.66, 211.67, 211.69, 211.71, 211.73, 211.75, 211.78, 212.10, 212.12, 212.13, 212.34, 212.53, 212.54, 212.56, 212.58, 212.60, 212.98, 213.02, 213.04, 213.41, 213.44, 213.47, 213.87, 213.90, 214.29, 214.36, 214.74, 215.20, 215.61, 215.68, 215.70, 216.05, 216.07, 216.10, 216.50, 216.54, 216.56, 216.94, 216.95, 216.97, 217.00, 217.37, 217.43, 217.45, 217.85, 218.27, 218.29, 218.75, 218.77, 219.15, 219.15, 219.19, 219.37, 219.43, 219.57, 219.59, 219.75 };
//= { 1.92, 1.96, 2.01, 2.09, 15.58, 15.63, 15.75, 16.04, 16.07, 16.11, 16.2, 23.08, 23.13, 23.17, 23.25, 30.14, 30.2, 30.22, 30.24, 30.55, 30.58, 30.62, 31.02, 31.03, 31.04, 31.08, 31.47, 31.54, 31.91, 31.96, 31.98, 32, 32.36, 32.8, 32.86, 33.24, 33.62, 33.66, 33.74, 34.11, 34.12, 34.55, 34.63, 35, 35.09, 35.44, 35.53, 35.83, 35.84, 35.87, 35.95, 36.28, 36.32, 36.35, 36.77, 36.98, 37, 37.03, 37.21, 37.27, 37.64, 37.74, 38.09, 38.13, 38.15, 38.52, 38.96, 39.4, 39.48, 39.5, 39.85, 40.28, 40.72, 40.82, 41.17, 41.63, 41.64, 41.68, 41.7, 42.05, 42.49, 42.52, 42.93, 43, 43.34, 43.36, 43.44, 43.46, 43.81, 43.85, 43.86, 43.88, 44.05, 44.1, 44.26, 44.69, 44.77, 45.13, 45.57, 45.67, 46.02, 46.11, 46.46, 46.9, 46.99, 47.34, 47.44, 47.73, 47.74, 47.78, 48.23, 48.66, 48.73, 49.1, 49.11, 49.54, 49.98, 50.43, 50.5, 50.86, 51.08, 51.09, 51.11, 51.14, 51.32, 51.32, 51.38, 51.74, 51.84, 52.15, 52.18, 52.63, 53.06, 53.51, 53.61, 53.96, 54.02, 54.05, 54.39, 54.78, 54.83, 55.27, 55.72, 56.15, 56.25, 56.6, 57.04, 57.04, 57.13, 57.47, 57.57, 57.93, 58.14, 58.36, 58.36, 58.43, 58.45, 58.81, 59.24, 59.33, 59.68, 60.12, 60.56, 60.57, 60.66, 61.01, 61.45, 61.52, 61.84, 61.85, 61.88, 62.32, 62.4, 62.77, 62.84, 63.22, 63.65, 63.72, 64.08, 64.18, 64.53, 64.54, 64.6, 64.98, 64.99, 65.2, 65.21, 65.42, 65.86, 66.29, 66.31, 66.33, 66.74, 66.76, 66.81, 67.18, 67.62, 68.02, 68.05, 68.5, 68.6, 68.94, 69.01, 69.39, 69.83, 70.26, 70.36, 70.7, 71.15, 71.24, 71.58, 72.03, 72.06, 72.24, 72.32, 72.47, 72.54, 72.91, 73.34, 73.35, 73.37, 73.4, 73.42, 73.79, 74.23, 74.33, 74.67, 74.68, 75.11, 75.57, 75.59, 75.96, 75.99, 76.4, 76.43, 76.51, 76.87, 76.97, 77.31, 77.32, 77.72, 77.75, 77.81, 77.83, 78.19, 78.64, 78.71, 79.07, 79.31, 79.34, 79.35, 79.37, 79.53, 79.59, 79.97, 80.06, 80.41, 80.46, 80.48, 80.84, 80.94, 81.28, 81.29, 81.72, 81.8, 82.16, 82.17, 82.18, 82.22, 82.24, 82.61, 82.68, 83.05, 83.07, 83.12, 83.49, 83.54, 83.56, 83.93, 84.39, 84.42, 84.44, 84.82, 84.86, 84.88, 85.07, 85.11, 85.13, 85.27, 85.29, 85.31, 85.33, 85.51, 85.71, 85.95, 85.99, 86.01, 86.15, 86.17, 86.19, 86.21, 86.38, 86.39, 86.41, 86.43, 86.58, 93.63, 93.66, 93.79, 95.37, 95.4, 95.43, 95.51, 95.55, 95.58, 96.06, 96.09, 96.22, 96.22, 96.72, 96.75, 96.77, 96.79, 96.88, 97.16, 97.19, 97.21, 97.23, 97.32, 100.67, 100.77, 100.86, 114.36, 114.39, 114.42, 114.51, 114.57, 114.59, 114.65, 114.79, 114.82, 114.84, 114.87, 114.88, 121.83, 121.86, 121.88, 121.9, 122, 128.44, 128.47, 128.51, 128.6, 128.65, 128.87, 128.93, 150.04, 150.14, 150.49, 150.5, 150.52, 150.94, 150.98, 151.37, 151.4, 151.44, 151.81, 151.82, 151.84, 151.86, 151.88, 152.27, 152.28, 152.69, 152.7, 152.76, 153.13, 153.16, 153.18, 153.58, 153.59, 154, 154.4, 154.45, 154.48, 154.5, 154.52, 154.9, 154.94, 154.96, 155.34, 155.35, 155.4, 155.42, 155.45, 155.74, 155.79, 155.81, 156.18, 156.22, 156.66, 156.71, 156.88, 157.11, 157.12, 157.54, 157.59, 157.98, 157.99, 158.01, 158.03, 158.05, 158.42, 158.45, 158.87, 158.88, 158.93, 159.32, 159.75, 159.76, 160.19, 160.2, 160.23, 160.26, 160.63, 160.64, 160.67, 160.7, 161.07, 161.08, 161.1, 161.14, 161.51, 161.52, 161.58, 161.95, 161.98, 162.02, 162.39, 162.4, 162.42, 162.46, 162.83, 162.86, 162.88, 163.27, 163.27, 163.32, 163.71, 163.76, 163.93, 163.95, 163.96, 163.98, 164, 164.17, 164.18, 164.61, 164.64, 164.67, 165.07, 165.08, 165.48, 165.49, 165.92, 165.99, 166.36, 166.8, 167.24, 167.29, 167.68, 167.75, 168.12, 168.17, 168.19, 168.57, 168.58, 168.99, 169.05, 169.46, 169.89, 169.94, 170.33, 170.77, 170.8, 170.98, 171, 171.04, 171.21, 171.22, 171.24, 171.26, 171.28, 171.3, 171.64, 171.66, 172.1, 172.1, 172.12, 172.14, 172.53, 172.6, 172.97, 173.41, 173.42, 173.87, 173.88, 174.3, 174.35, 174.36, 174.74, 174.8, 175.18, 175.19, 175.21, 175.23, 175.62, 175.69, 176.09, 176.11, 176.13, 176.15, 176.51, 176.53, 176.94, 176.99, 177.01, 177.01, 177.4, 177.43, 178.11, 178.3, 178.31, 178.71, 178.72, 178.75, 179.17, 179.17, 179.19, 179.62, 179.64, 179.66, 180.03, 180.09, 180.12, 180.47, 180.48, 180.5, 180.91, 181.34, 181.4, 181.42, 181.79, 181.8, 181.86, 182.25, 182.68, 182.74, 183.13, 183.56, 183.58, 183.99, 183.99, 184.04, 184.43, 184.45, 184.48, 184.51, 184.53, 184.55, 184.91, 184.95, 185.11, 185.15, 185.17, 185.34, 185.35, 185.79, 185.83, 186.2, 186.21, 186.23, 186.25, 186.27, 186.64, 187.08, 187.13, 187.15, 187.52, 187.54, 187.57, 187.59, 187.97, 188, 188.03, 188.44, 188.84, 188.88, 188.9, 189.29, 189.32, 189.34, 189.73, 189.76, 189.78, 189.8, 190.17, 190.18, 190.2, 190.61, 190.66, 190.7, 190.72, 190.87, 190.88, 190.9, 191.06, 191.3, 191.32, 191.34, 191.76, 191.78, 191.95, 192.19, 192.23, 192.39, 192.86, 192.88, 193.27, 193.71, 193.77, 194.15, 194.17, 194.2, 194.59, 195.03, 195.05, 195.08, 195.49, 195.51, 195.53, 195.83, 195.91, 195.93, 195.95, 195.97, 195.99, 196.33, 196.34, 196.36, 196.37, 196.39, 196.41, 196.8, 196.83, 197.22, 197.24, 197.67, 197.71, 197.73, 197.75, 197.78, 198.12, 198.55, 199, 199.06, 199.21, 199.27, 199.43, 199.44, 199.46, 199.48, 199.5, 199.89, 199.9, 200.33, 200.38, 200.75, 200.8, 200.82, 201.19, 201.21, 201.26, 201.63, 201.66, 201.68, 202.07, 202.14, 202.52, 202.54, 202.56, 202.97, 202.99, 203.02, 203.4, 203.41, 203.42, 203.44, 203.47, 203.84, 203.89, 203.91, 204.28, 204.31, 204.33, 204.73, 204.83, 204.85, 205.16, 205.19, 205.23, 205.6, 206.04, 206.27, 206.5, 206.51, 206.53, 206.55, 206.92, 206.94, 207.36, 207.39, 207.41, 207.43, 207.81, 207.82, 207.88, 208.25, 208.31, 208.68, 208.7, 209.13, 209.14, 209.18, 209.57, 209.58, 210.01, 210.02, 210.08, 210.45, 210.54, 210.91, 210.96, 211.35, 211.41, 211.79, 211.81, 211.82, 211.84, 212.19, 212.21, 212.23, 212.26, 212.28, 212.67, 212.68, 212.7, 212.72, 212.74, 212.76, 212.79, 213.11, 213.13, 213.35, 213.55, 213.57, 213.59, 213.61, 213.99, 214.01, 214.03, 214.05, 214.42, 214.45, 214.49, 214.88, 214.91, 215.3, 215.76, 216.22, 216.63, 216.69, 216.72, 217.06, 217.08, 217.09, 217.11, 217.51, 217.55, 217.58, 217.95, 217.96, 217.98, 218.02, 218.38, 218.44, 218.46, 218.86, 219.29, 219.3, 219.76, 219.78, 220.17, 220.2, 220.45, 220.58, 220.76, };
//float spawnTimes[TOTAL_SPAWNS] = { 0.11, 2.41, 4.86, 7.10, 8.45, 8.47, 8.74, 8.8, 9.05, 9.07, 9.65, 9.95, 9.95, 10.01, 10.54, 10.61, 10.84, 11.14, 11.21, 11.44, 11.82, 12.05, 12.07, 12.34, 12.42, 12.43, 12.45, 12.64, 12.94, 13.01, 13.24, 13.25, 13.54, 13.57, 13.61, 13.84, 14.14, 14.23, 14.44, 14.47, 14.82, 15.05, 15.34, 15.41, 15.64, 15.94, 16.24, 16.55, 16.61, 16.65, 16.66, 16.83, 17.14, 17.17, 17.45, 17.74, 18.34, 18.41, 18.79, 18.86, 18.09, 19.11, 19.12, 19.18, 19.20, 21.75, 24.10, 26.66, 26.7, 26.9, 26.97, 27.19, 27.49, 27.80, 28.24, 28.31, 28.69, 28.76, 28.84, 29.14, 29.22, 29.75, 29.81, 30.04, 30.35, 30.41, 30.64, 30.95, 31.02, 31.24, 31.55, 31.62, 31.85, 32.14, 32.21, 32.44, 32.75, 32.75, 32.77, 32.82, 32.83, 33.04, 33.34, 33.42, 33.64, 33.65, 33.67, 33.94, 34.01, 34.25, 34.55, 34.62, 34.85, 35.16, 35.21, 35.74, 35.82, 36.34, 36.41, 36.64, 36.94, 37.01, 37.54, 37.62, 37.69, 37.76, 38.21, 38.29, 38.37, 38.44, 38.74, 38.81, 39.34, 39.42, 39.65, 40.01, 40.24, 40.54, 40.62, 40.84, 40.87, 41.14, 41.21, 41.45, 41.82, 42.04, 42.35, 42.42, 42.43, 42.64, 42.94, 42.97, 43.02, 43.05, 43.24, 43.55, 43.61, 43.65, 43.84, 44.15, 44.23, 44.44, 44.75, 44.81, 44.85, 45.04, 45.34, 45.42, 46.99, 47.28, 47.6, 47.6, 47.89, 48.43, 48.49, 48.58, 48.71, 48.86, 49.1, 49.24, 49.32, 49.39, 49.47, 49.5, 49.51, 49.52, 49.61, 49.71, 49.77, 49.99, 50.09, 50.11, 50.14, 50.29, 50.3, 50.36, 50.61, 50.82, 51.19, 51.42, 51.49, 51.5, 51.65, 52.17, 52.26, 52.32, 53.15, 53.23, 53.28, 53.33, 53.68, 53.74, 53.96, 54.34, 54.41, 54.65, 54.71, 55.09, 55.17, 57.05, 57.07, 57.35, 57.39, 57.64, 57.94, 58.01, 58.54, 58.85, 59.15, 59.22, 59.23, 59.44, 59.75, 59.75, 59.81, 59.84, 59.86, 60.05, 60.34, 60.42, 60.65, 60.94, 61.01, 61.04, 61.07, 61.24, 61.55, 61.61, 61.84, 62.15, 62.21, 62.75, 62.82, 62.85, 63.05, 63.05, 63.07, 63.09, 63.42, 63.64, 63.67, 63.94, 64.01, 64.06, 64.24, 64.25, 64.54, 64.63, 64.85, 64.87, 65.14, 65.17, 65.21, 65.25, 65.46, 65.74, 66.12, 66.64, 66.67, 66.84, 67.01, 67.12, 67.14, 67.25, 67.54, 67.57, 67.62, 67.84, 67.87, 68.21, 68.44, 68.74, 68.83, 69.36, 69.41, 69.65, 69.94, 70.02, 70.24, 70.61, 70.84, 71.14, 71.21, 71.82, 71.83, 72.28, 72.33, 72.43, 72.5, 72.57, 72.66, 73.1, 73.46, 73.5, 73.61, 73.77, 74.14, 74.66, 74.81, 75.28, 75.49, 75.56, 77.15, 77.22, 77.23, 77.45, 77.82, 78.04, 78.35, 78.37, 78.41, 78.45, 78.66, 78.94, 79.01, 79.24, 79.62, 80.22, 80.74, 80.75, 80.81, 81.04, 81.35, 81.41, 81.88, 82.32, 82.48, 82.5, 82.55, 82.62, 82.69, 82.7, 82.91, 83.38, 83.67, 83.74, 83.97, 83.98, 84.06, 84.12, 84.42, 84.66, 84.87, 85.18, 85.2, 85.25, 85.55, 85.57, 85.84, 85.88, 85.94, 86.14, 86.29, 86.36, 86.44, 86.45, 86.74, 86.82, 87.34, 87.41, 87.64, 87.65, 87.95, 88.01, 88.26, 88.28, 88.54, 88.62, 88.84, 89.15, 89.15, 89.17, 89.22, 89.81, 90.04, 90.36, 90.43, 90.64, 90.67, 90.94, 90.95, 91.02, 91.62, 91.99, 92.06, 92.3, 93.66, 93.94, 94.02, 94.55, 94.63, 94.84, 95.14, 95.22, 95.45, 95.75, 95.82, 95.82, 96.04, 96.07, 96.34, 96.41, 96.65, 96.94, 97.01, 97.25, 97.54, 97.62, 97.84, 97.85, 98.15, 98.22, 98.44, 98.45, 98.74, 98.82, 98.83, 99.04, 99.34, 99.42, 99.64, 99.94, 99.97, 100.01, 100.24, 100.55, 101.14, 101.17, 101.21, 101.74, 101.83, 101.85, 102.05, 102.34, 102.64, 102.94, 103.23, 103.54, 103.62, 103.85, 103.87, 104.19, 104.21, 104.44, 104.74, 104.81, 105.04, 105.07, 105.64, 105.94, 106.02, 106.03, 106.05, 106.54, 106.61, 106.84, 107.22, 107.75, 107.82, 108.04, 108.42, 108.64, 108.67, 108.94, 109.01, 109.24, 109.55, 109.61, 109.84, 110.14, 110.22, 110.23, 110.44, 110.45, 110.74, 110.81, 110.85, 111.49, 111.56, 111.64, 112.24, 112.66, 112.84, 115.24, 115.84, 115.99, 116.44, 117.04, 117.05, 117.19, 117.65, 118.24, 118.4, 118.4, 118.84, 119.44, 119.62, 120.04, 120.65, 120.79, 120.8, 121.39, 121.43, 121.47, 121.85, 121.92, 122.29, 122.3, 122.36, 124.84, 125.14, 125.22, 125.45, 125.45, 125.47, 125.81, 126.04, 126.41, 126.45, 126.64, 126.94, 126.97, 127.02, 127.25, 127.28, 127.54, 127.61, 127.86, 128.14, 128.22, 128.44, 128.75, 128.77, 128.82, 128.85, 129.04, 129.34, 129.43, 129.66, 129.94, 130.02, 130.25, 130.54, 130.62, 130.84, 131.15, 131.45, 131.74, 131.81, 132.34, 132.37, 132.41, 132.64, 132.94, 133.02, 133.26, 134.53, 134.59, 134.67, 134.68, 134.82, 134.89, 134.97, 134.98, 135.19, 135.2, 135.35, 135.49, 135.52, 135.54, 135.64, 135.88, 136.02, 136.05, 136.06, 136.39, 136.47, 136.76, 137.6, 137.68, 137.74, 138.04, 139.47, 139.55, 139.69, 139.74, 139.92, 140.08, 140.14, 140.16, 140.37, 140.68, 140.7, 140.74, 140.82, 140.83, 140.89, 141.2, 141.2, 141.28, 141.3, 141.34, 141.35, 141.43, 141.49, 141.57, 143.14, 143.45, 143.74, 144.34, 144.41, 144.94, 145.02, 145.62, 145.63, 145.85, 146.15, 146.22, 146.25, 146.26, 146.46, 146.75, 146.83, 147.34, 147.42, 147.45, 147.65, 147.96, 147.97, 148.01, 148.24, 148.54, 148.61, 149.14, 149.15, 149.17, 149.21, 149.44, 149.45, 149.47, 149.49, 149.82, 150.04, 150.34, 150.42, 150.65, 150.95, 151.03, 151.24, 151.55, 151.63, 152.14, 152.22, 152.44, 152.76, 152.77, 153.05, 153.09, 153.13, 153.16, 153.34, 153.41, 153.45, 153.46, 153.64, 153.94, 154.03, 154.24, 154.61, 154.85, 155.15, 155.21, 155.23, 155.45, 155.74, 155.81, 156.04, 156.34, 156.35, 156.37, 156.42, 156.64, 156.68, 157.02, 157.24, 157.54, 157.61, 157.85, 158.14, 158.16, 158.22, 158.59, 158.83, 158.89, 158.97, 159, 159.21, 159.27, 159.5, 159.73, 159.79, 159.88, 160.01, 160.16, 160.4, 160.48, 160.54, 160.55, 160.69, 160.76, 161.07, 161.45, 161.52, 161.89, 161.96, 162.05, 163.55, 163.62, 163.65, 164.14, 164.44, 164.75, 164.82, 164.83, 165.06, 165.35, 165.42, 165.45, 165.64, 165.65, 165.95, 165.97, 166.02, 166.55, 166.61, 166.86, 167.14, 167.22, 167.44, 167.74, 167.82, 167.82, 168.28, 168.65, 168.88, 168.95, 169.03, 169.09, 169.18, 169.31, 169.47, 169.48, 169.92, 169.93, 170.07, 170.36, 170.51, 170.61, 170.67, 171.35, 171.37, 171.64, 171.96, 172.26, 172.54, 173.14, 173.17, 173.23, 173.74, 173.82, 174.35, 174.37, 174.42, 174.66, 174.95, 175.02, 175.26, 175.62, 176.14, 176.44, 176.74, 176.77, 176.82, 177.04, 177.07, 177.34, 177.41, 177.64, 177.88, 178.1, 178.17, 178.26, 178.31, 178.41, 178.47, 178.55, 178.62, 178.84, 180.35, 180.42, 180.65, 180.65, 180.95, 181.26, 181.55, 181.63, 181.85, 182.14, 182.23, 182.44, 182.74, 182.82, 183.05, 183.34, 183.41, 183.65, 183.67, 183.94, 184.02, 184.03, 184.25, 184.54, 184.61, 184.86, 185.14, 185.21, 185.44, 185.74, 185.82, 186.04, 186.35, 186.42, 186.65, 186.95, 187.02, 187.24, 187.54, 187.57, 187.61, 187.85, 187.87, 188.21, 188.25, 188.74, 188.75, 188.89, 188.97, 189.33, 189.43, 189.64, 189.67, 190.02, 190.24, 190.54, 190.61, 190.86, 191.14, 191.21, 191.44, 191.47, 191.74, 191.82, 191.83, 192.04, 192.07, 192.34, 192.37, 192.42, 192.43, 192.64, 192.94, 193.01, 193.25, 193.63, 194.16, 194.22, 194.45, 194.81, 195.04, 195.07, 195.41, 195.64, 195.94, 195.97, 196.01, 196.25, 196.55, 196.57, 196.61, 196.85, 196.87, 197.18, 197.75, 198.04, 198.35, 198.64, 199.06, 199.15, 200.44, 200.74, 200.75, 200.82, 201.04, 201.08, 201.41, 201.65, 201.94, 202.24, 202.54, 202.62, 202.85, 203.14, 203.17, 203.21, 203.45, 203.75, 203.75, 203.81, 204.04, 204.35, 204.42, 204.43, 204.64, 204.95, 205.25, 205.54, 205.55, 205.62, 205.85, 206.15, 206.22, 206.44, 206.76, 206.82, 206.83, 207.05, 207.42, 207.93, 207.95, 207.98, 208.24, 208.27, 208.29, 208.34, 208.39, 208.54, 208.55, 208.57, 208.72, 208.84, 208.87, 208.89, 208.91, 209.45, 209.75, 209.81, 210.04, 210.35, 210.42, 210.46, 210.64, 210.67, 210.69, 211.01, 211.26, 211.55, 211.56, 211.62, 211.63, 211.84, 212.15, 212.23, 212.44, 212.75, 212.81, 213.34, 213.43, 213.64, 213.95, 213.98, 214.01, 214.24, 214.55, 214.63, 214.84, 215.14, 215.22, 215.46, 215.47, 215.74, 215.82, 216.04, 216.34, 216.35, 216.42, 216.65, 216.94, 217.02, 218.74, 218.83, 219.2, 219.27, 219.49, 219.58, 219.96, 220.01, 220.24, 220.54, 220.61, 220.84, 220.87, 221.14, 221.15, 221.21, 221.25, 221.26, 221.44, 221.74, 221.81, 222.04, 222.42, 222.65, 222.95, 223.24, 223.54, 223.62, 223.84, 224.15, 224.21, 224.45, 224.74, 225.06, 225.34, 225.41, 225.64, 225.94, 226.01, 226.25, 226.27, 226.54, 226.63, 227.16, 227.22, 227.23, 227.45, 227.75, 227.82, 228.19, 228.22, 228.26, 228.49, 228.52, 228.56, 228.81, 228.87, 229.08, 229.16, 229.24, 229.54, 229.61, 229.85, 229.86, 230.14, 230.22, 230.23, 230.45, 230.75, 230.81, 231.05, 231.35, 231.35, 231.41, 231.43, 231.65, 231.94, 232.02, 232.25, 232.27, 232.56, 232.61, 232.84, 233.15, 233.21, 233.23, 233.45, 233.74, 233.83, 234.05, 234.35, 234.37, 234.42, 234.64, 234.94, 235.25, 235.54, 235.62, 235.85, 236.14, 236.21, 236.45, 236.47, 236.74, 236.83, 237.05, 237.07, 237.36, 237.42, 237.66, 238.09, 238.54, 238.84, 239.15, 239.15, 239.22, 239.45, 239.47, 239.81, 240.05, 240.34, 240.41, 240.45, 240.64, 241.03, 241.04, 241.24, 241.27, 241.54, 241.61, 241.84, 242.22, 242.45, 242.74, 242.81, 243.3, 243.31, 243.32, 243.34, 243.66, 243.95, 244.01, 244.25, 244.25, 244.54, 244.62, 244.84, 245.16, 245.21, 245.44, 245.74, 245.77, 246.05, 246.07, 246.35, 246.64, 247.01, 247.24, 247.55, 247.85, 248.14, 248.74, 248.77, 248.82, 249.06, 249.34, 249.41, 249.64, 249.65, 249.94, 250.01, 250.24, 250.55, 250.61, 250.85, 251.14, 251.17, 251.22, 251.44, 251.74, 251.82, 251.83, 252.05, 252.35, 252.42, 252.64, 252.94, 253.02, 253.03, 253.48, 253.54, 253.86, 253.92, 254.08, 254.15, 254.3, 254.45, 254.51, 254.53, 254.6, 254.67, 254.83, 255.11, 255.2, 255.21, 255.27, 255.43, 255.57, 255.58, 255.65, 255.71, 255.95, 256.02, 256.09, 256.16, 256.24, 256.26, 256.47, 256.48, 256.61, 256.69, 256.78, 257.82, 257.92, 257.97, 257.99, 258.06, 258.34, 258.37, 258.42, 258.45, 258.94, 259.02, 259.25, 259.54, 259.61, 259.84, 260.14, 260.21, 260.45, 260.68, 260.76, 260.82, 260.83, 260.9, 260.91, 261.12, 261.13, 261.42, 261.66, 261.69, 261.79, 261.88, 261.94, 262.11, 262.17, 262.2, 262.24, 262.32, 262.92, 262.93, 263.01, 263.07, 263.08, 263.38, 263.46, 263.52, 263.6, 263.67, 263.83, 263.96, 264.2, 264.42, 264.5, 264.57, 264.8, 264.86, 265.02, 265.18, 265.39, 265.43, 265.47, 265.55, 265.56, 265.7, 265.72, 265.76, 265.99, 266.07, 266.29, 266.38, 266.44, 267.65, 267.95, 268.01, 268.54, 268.62, 268.84, 269.16, 269.17, 269.21, 269.46, 269.74, 269.82, 269.85, 270.05, 270.35, 270.42, 270.66, 271.01, 271.26, 271.54, 271.61, 271.84, 271.87, 272.22, 272.68, 272.75, 273.12, 273.28, 273.35, 273.42, 273.49, 273.51, 273.71, 274.18, 274.32, 274.47, 274.63, 274.77, 274.78, 274.8, 274.86, 275.07, 275.11, 275.14, 275.23, 275.29, 275.3, 275.31, 275.34, 275.36, 275.44, 275.53, 275.59, 275.6, 275.76, 275.81, 275.97, 275.98, 276.41, 276.83, 276.86, 277.09, 277.17, 277.2, 277.24, 277.56, 278.22, 278.44, 278.45, 278.76, 278.77, 279.05, 279.43, 280.01, 280.32, 280.47, 280.78, 280.93, 281.08, 281.22, 281.51, 281.53, 281.82, 282.96, 289.46, 289.54, 289.58, 289.65, 290.03, 290.33, 290.37, 290.51, 290.66, 291.09, 291.23, 291.24, 291.38, 291.66, 294.86, 294.88, 295.02, 295.03, 295.04, 295.22, 297.44 };
float hasSpawned[TOTAL_SPAWNS] = { };
// Objects (Global)
SpaceShip *ship;
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
std::list<GameObject *>::iterator iter2;
Background *titleScreen;
Background *lostScreen;
ALLEGRO_SAMPLE_INSTANCE *songInstance;
ALLEGRO_SAMPLE_INSTANCE *lossSongInst;
ALLEGRO_AUDIO_STREAM *songStream;

float stateTime = 0;
// Main prototype functions
void __cdecl TakeLife();
void __cdecl ScorePoint();
void ChangeState(int &state, int newState);
void DrawPercentBar(int x, int y, int w, int h, float percent, ALLEGRO_BITMAP * border, ALLEGRO_BITMAP * bar, ALLEGRO_FONT* font);

int main(int argc, char **argv) {
	int currentSpawn = 0;
	for (int i = 0; i < TOTAL_SPAWNS; i++){
		hasSpawned[i] = false;
	}

	// Local variables
	bool done = false;
	bool render = false;
	bool showColBox = false;

	int frames = 0;
	int gameFPS = 0;
	float elapsedTime = 0;
	float initTime = 0;
	float gameTime = 0;
	float lastFound = 0;

	ship = new SpaceShip();	

	// Init state as -1 (no state)
	int state = -1;

	// Allegro Variables
	ALLEGRO_BITMAP *shipImage = NULL;
	ALLEGRO_BITMAP *cometImage = NULL;
	ALLEGRO_BITMAP *explImage = NULL;
	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;
	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *lostImage = NULL;
	ALLEGRO_BITMAP *healthbar_border = NULL;
	ALLEGRO_BITMAP *healthbar_bar = NULL;
	ALLEGRO_BITMAP *top_bar = NULL;
	ALLEGRO_SAMPLE *shot = NULL;
	ALLEGRO_SAMPLE *boom = NULL;
	ALLEGRO_SAMPLE *death = NULL;
	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE *lost_song = NULL;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	ALLEGRO_FONT *arial_font12;
	ALLEGRO_FONT *arial_font18;
	ALLEGRO_FONT *arial_font28;

	ALLEGRO_FONT *pix_font12_rg;
	ALLEGRO_FONT *pix_font16_rg;
	ALLEGRO_FONT *pix_font18_rg;
	ALLEGRO_FONT *pix_font28_rg;

	ALLEGRO_FONT *pix_font12_b;
	ALLEGRO_FONT *pix_font18_b;
	ALLEGRO_FONT *pix_font28_b;

	ALLEGRO_TRANSFORM cam;
	int camX = 0, camY = 0;
	float camAng = 0.0;
	
	// Init Allegro
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);

	if(!display)
		return -1;

	al_set_window_title(display, "SpaceFace (No Grey) - By Ryan (MrBotox) Thorn - v0.1");

	// Addon init and installs
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	// Init variables

	arial_font12 = al_load_font("media/font/arial.ttf", 12, 0);
	arial_font18 = al_load_font("media/font/arial.ttf", 18, 0);
	arial_font28 = al_load_font("media/font/arial.ttf", 28, 0);

	pix_font12_rg = al_load_font("media/font/pixarial_RG.ttf", 12, 0);
	pix_font16_rg = al_load_font("media/font/pixarial_RG.ttf", 16, 0);
	pix_font18_rg = al_load_font("media/font/pixarial_RG.ttf", 18, 0);
	pix_font28_rg = al_load_font("media/font/pixarial_RG.ttf", 28, 0);

	pix_font12_b = al_load_font("media/font/pixarial_B.ttf", 12, 0);
	pix_font18_b = al_load_font("media/font/pixarial_B.ttf", 18, 0);
	pix_font28_b = al_load_font("media/font/pixarial_B.ttf", 28, 0);

	al_reserve_samples(15);

	bgImage = al_load_bitmap("media/img/starBG.png");
	mgImage = al_load_bitmap("media/img/starMG-kappa.png");
	fgImage = al_load_bitmap("media/img/starFG.png");
	
	healthbar_border = al_load_bitmap("media/img/healthbar_border.png");
	healthbar_bar = al_load_bitmap("media/img/healthbar_bar.png");
	top_bar = al_load_bitmap("media/img/top_bar.png");

	Background *bg = new Background(bgImage, 1);
	objects.push_back(bg);

	bg = new Background(mgImage, 2);
	objects.push_back(bg);

	bg = new Background(fgImage, 3);
	objects.push_back(bg);

	shipImage = al_load_bitmap("media/img/datsheffy-ship.png");
	ship->Init(shipImage);

	objects.push_back(ship);

	cometImage = al_load_bitmap("media/img/comet.png");
	explImage = al_load_bitmap("media/img/explosion_3_40_128.png");

	titleImage = al_load_bitmap("media/img/Shooter_Title.png");
	lostImage = al_load_bitmap("media/img/Shooter_Lose.png");

	titleScreen = new Background(titleImage, 0);
	lostScreen = new Background(lostImage, 0);

	shot = al_load_sample("media/sound/pew-formal.ogg");
	boom = al_load_sample("media/sound/ow.ogg");
	death = al_load_sample("media/sound/death.ogg");
	song = al_load_sample("media/sound/darude.ogg");
	lost_song = al_load_sample("media/sound/loss-music.ogg");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	lossSongInst = al_create_sample_instance(lost_song);
	al_set_sample_instance_playmode(lossSongInst, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(lossSongInst, al_get_default_mixer());

	ChangeState(state, TITLE);

	srand(time(NULL));

	// Timer Init and Start

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();
	initTime = al_current_time();
	while(!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		// User Inputs
		
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					if (state == TITLE) {
						ChangeState(state, PLAYING);
					} else if (state == PLAYING) {
						Bullet *bullet1 = new Bullet(ship->GetX() + 15, ship->GetY() - 30, &ScorePoint);
						Bullet *bullet2 = new Bullet(ship->GetX() + 15, ship->GetY(), &ScorePoint);
						Bullet *bullet3 = new Bullet(ship->GetX() + 15, ship->GetY() + 30, &ScorePoint);
						objects.push_back(bullet1);
						objects.push_back(bullet2);
						objects.push_back(bullet3);
						al_play_sample(shot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					break;
				case ALLEGRO_KEY_F:
					if (state == LOST) {
						ChangeState(state, PLAYING);
					}
					break;
				case ALLEGRO_KEY_F1:
					if (state == PLAYING) {
						showColBox = !showColBox;
					}
					break;

			}
		} else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;
			}
		} else if(ev.type == ALLEGRO_EVENT_TIMER) {
			// Update Game Objs
			render = true;
			frames++;
			
			if (elapsedTime >= 300){
				ChangeState(state, WIN);
			}

			if (al_current_time() - gameTime >= 1) {
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			if (state == PLAYING) {
				elapsedTime = roundf((al_current_time() - stateTime) * 100) / 100;
				if(keys[UP])
					ship->MoveUp();
				else if(keys[DOWN])
					ship->MoveDown();
				else
					ship->ResetAnimation(1);

				if(keys[LEFT])
					ship->MoveLeft();
				else if(keys[RIGHT])
					ship->MoveRight();
				else
					ship->ResetAnimation(0);

				size_t spawnTimesSize = sizeof(spawnTimes) / sizeof(int);
				float *end = spawnTimes + spawnTimesSize;

				auto it = std::find(spawnTimes, end, elapsedTime);
				if (it >= end) {
					std::cout << "No Spawn" << std::endl;
				} else {
					if (hasSpawned[it - spawnTimes] == false) {
						std::cout << "Spawn" << std::endl;
						Comet *comet = new Comet(WIDTH, 100 + rand() % (HEIGHT - 110), cometImage, &TakeLife);
						objects.push_back(comet);

						hasSpawned[it - spawnTimes] = true;
						currentSpawn++;
					} else {
						std::cout << "Already Spawned" << std::endl;
					}
				}

				//if(rand() % 50 == 0) {
				//	Comet *comet = new Comet(WIDTH, 30 + rand() % (HEIGHT - 60), cometImage, &TakeLife);
				//	objects.push_back(comet);
				//}

				// updates and collisions
				for (iter = objects.begin(); iter != objects.end(); ++iter) {
					(*iter)->Update();
				}
					
				for(iter = objects.begin(); iter != objects.end(); ++iter) {
					if (!(*iter)->Collidable()) {
						continue;
					}

					for(iter2 = iter; iter2 != objects.end(); ++iter2) {
						if (!(*iter2)->Collidable()) {
							continue;
						}
						
						if ((*iter)->GetID() == (*iter2)->GetID()) {
							continue;
						}

						if ((*iter)->CheckCollisions((*iter2))) {
							(*iter)->Collided((*iter2)->GetID());
							(*iter2)->Collided((*iter)->GetID());

							Explosion *explosion = new Explosion(((*iter)->GetX() + (*iter2)->GetX()) / 2, ((*iter)->GetY() + (*iter2)->GetY()) / 2, explImage);

							objects.push_back(explosion);
							al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}
					}
				}

				if (ship->GetLives() <= 0) {
					al_play_sample(death, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					ChangeState(state, LOST);
				}
			}

			// delete dead objects
			for(iter = objects.begin(); iter != objects.end(); ) {
				if(! (*iter)->GetAlive()) {
					delete (*iter);
					iter = objects.erase(iter);
				} else {
					iter++;
				}
			}

		}

		// Rendering of game
		if(render && al_is_event_queue_empty(event_queue)) {
			render = false;
			if(state == TITLE) {
				titleScreen->Render();
			} else if(state == PLAYING) {
				for (iter = objects.begin(); iter != objects.end(); ++iter) {
					(*iter)->Render();
					if (showColBox)
						(*iter)->ToggleRenderColBox();
				}
				al_draw_scaled_bitmap(top_bar, 0, 0, 640, 30, 0, 0, 1280, 60, 0);
				DrawPercentBar(70, 10, 290, 30, ship->GetLifePercent(), healthbar_border, healthbar_bar, pix_font12_rg);
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH - 205, 14, 0, "Time: %i", (int)round(elapsedTime));
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH - 410, 14, 0, "Score: %i", ship->GetScore());
				al_draw_textf(pix_font16_rg, al_map_rgb(200, 200, 200), WIDTH / 2, 14, 0, "Spawned: %i", currentSpawn);
				//al_draw_textf(font18, al_map_rgb(255, 255, 255), 10, 30, 0, "%i lives left. RIP'D %i Kappas", ship->GetLives(), ship->GetScore());
				camAng += 0.1;
				if (camAng >= 0.1){
					camAng = 0.0;
				}
				else {
					camAng = 0.1;
				}
				if (camX == 0){
					camX = 5;
				}
				else if (camX == 5) {
					camX = 0;
				}
				if (camY == 0){
					camY = 5;
				}
				else if (camY == 5) {
					camY = 0;
				}
				if (elapsedTime > 29){
					al_identity_transform(&cam);
					al_translate_transform(&cam, -(WIDTH / 2) + camX, -(HEIGHT / 2) + camY);
					al_rotate_transform(&cam, camAng);
					al_translate_transform(&cam, WIDTH / 2, HEIGHT / 2);
					al_use_transform(&cam);
				}
			} else if(state == LOST) {
				lostScreen->Render();
			} else if (state == WIN) {
				al_draw_textf(pix_font18_b, al_map_rgb(255, 255, 255), WIDTH / 2 - 200, HEIGHT / 2, 0, "You won with a score of %i", ship->GetScore());
				al_draw_textf(pix_font18_b, al_map_rgb(255, 255, 255), WIDTH / 2 - 180, HEIGHT / 2 + 25, 0, "You lasted %f seconds", elapsedTime);
				al_draw_text(pix_font18_b, al_map_rgb(255, 0, 0), WIDTH - 200, HEIGHT - 25, 0, "This win screen is temporary");
			}
			
			al_draw_textf(pix_font12_rg, al_map_rgb(255, 255, 255), WIDTH - 80, HEIGHT - 50, 0, "FPS: %i", gameFPS);
			
			// Flip the buffer
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	// End of game loop clean up process
	for(iter = objects.begin(); iter != objects.end(); ) {
		(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	lostScreen->Destroy();
	titleScreen->Destroy();
	
	delete lostScreen;
	delete titleScreen;
	
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(explImage);
	al_destroy_bitmap(shipImage);
	al_destroy_bitmap(cometImage);
	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(lostImage);
	
	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample(lost_song);
	al_destroy_sample(shot);
	al_destroy_sample(death);
	
	al_destroy_sample_instance(lossSongInst);
	al_destroy_sample_instance(songInstance);

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	
	al_destroy_font(arial_font12);
	al_destroy_font(arial_font18);
	al_destroy_font(arial_font28);

	al_destroy_font(pix_font12_rg);
	al_destroy_font(pix_font16_rg);
	al_destroy_font(pix_font18_rg);
	al_destroy_font(pix_font28_rg);

	al_destroy_font(pix_font12_b);
	al_destroy_font(pix_font18_b);
	al_destroy_font(pix_font28_b);

	return 0;
}

// Misc functions

void __cdecl TakeLife() {
	ship->LoseLife();
}

void __cdecl ScorePoint() {
	ship->AddPoint();
}

void ChangeState(int &state, int newState) {
	stateTime = al_current_time();
	if(state ==TITLE) {
	
	} else if(state == PLAYING) {
		for(iter = objects.begin(); iter != objects.end(); ++iter) {
			if ((*iter)->GetID() != PLAYER && (*iter)->GetID() != MISC) {
				(*iter)->SetAlive(false);
			}
		}
		al_stop_sample_instance(songInstance);
	} else if(state == LOST) {
	
	}

	state = newState;

	if(state ==TITLE){
	
	} else if(state == PLAYING) {
		ship->Init();
		al_stop_sample_instance(lossSongInst);
		al_play_sample_instance(songInstance);
		
	} else if(state == LOST) {
		al_stop_sample_instance(songInstance);
		al_play_sample_instance(lossSongInst);
	}
}

void DrawPercentBar(int x, int y, int w, int h, float percent, ALLEGRO_BITMAP * border, ALLEGRO_BITMAP * bar, ALLEGRO_FONT* font) {
	al_draw_bitmap_region(bar, 0, 0, 5 + ((w) * percent / 100), y + h, x, y, 0);
	al_draw_bitmap(border, x, y, 0);
	al_draw_textf(font, al_map_rgb(255, 255, 255), x + w / 2, y + h / 2 - 8, ALLEGRO_ALIGN_CENTRE, "%i%%", (int)round(percent));
}