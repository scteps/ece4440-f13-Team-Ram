//int get_max(const int* arr, int arr_length)
//{
//  int i;
//  int max = arr[0];
//  for(i = 1; i < arr_length; ++i)
//  {
//    if(arr[i] >= max)
//    {
//      max = arr[i];
//    }
//  }
//  return max;
//}
//
//float get_scale_factor(int abs_dim, int max_val)
//{
//  float scale_factor;
//  if(abs_dim >= max_val)
//  {
//    scale_factor = abs_dim / max_val;
//  }
//  else
//  {
//    scale_factor = max_val / abs_dim;
//  }
//  return scale_factor;
//}

//void plot(int x_offset, const int* x_data, int scale_factor_x, int y_offset,
//    const int* y_data, int scale_factor_y, int values, int color,  alt_video_display* display  )
//{
//  int i;
//  // Plot the points
//  for(i = 1; i < values - 1; ++i)
//  {
////    point(x_offset + x_data[i] * scale_factor_x,
////        y_offset + y_data[i] * scale_factor_y);
//    vid_draw_line(x_offset + x_data[i-1] * scale_factor_x,
//        y_offset + y_data[i-1] * scale_factor_y,
//        x_offset + x_data[i] * scale_factor_x,
//        y_offset + y_data[i] * scale_factor_y,
//        1,
//        color,
//        display);
//  }
//}

