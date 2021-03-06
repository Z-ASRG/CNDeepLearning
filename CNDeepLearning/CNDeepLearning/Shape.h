#pragma once

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Util.h"
using namespace std;

namespace ASRG
{
	namespace ML
	{
		class Shape
		{
		public:
			uint32 width, height, depth, batch;
			//uint32 resolution, volume, size;
		public:
			Shape(uint32 width = 1, uint32 height = 1, uint32 depth = 1, uint32 batch = 1)
				:width(width), height(height), depth(depth), batch(batch)
			{
			};
			Shape(const Shape &S)
				:width(S.width), height(S.height), depth(S.depth), batch(S.batch)
			{
			};
			~Shape() {};

			Shape& operator=(const Shape &S)
			{
				width = S.width;
				height = S.height;
				depth = S.depth;
				batch = S.batch;

				return *this;
			};

			bool operator==(const Shape &S) const
			{
				if (width != S.width) { return false; }
				if (height != S.height) { return false; }
				if (depth != S.depth) { return false; }
				if (batch != S.batch) { return false; }

				return true;
			};

			bool operator!=(const Shape &S) const
			{
				return !(*this == S);
			};

			//Did not affect batch
			Shape operator+(const Shape &S) const
			{
				return Shape(width + S.width, height + S.height, depth + S.depth, batch);
			};
			Shape operator+(const uint32 Val) const
			{
				return Shape(width + Val, height + Val, depth + Val, batch);
			};

			//Did not affect batch
			Shape operator-(const Shape &S) const
			{
				return Shape(width - S.width, height - S.height, depth - S.depth, batch);
			};
			Shape operator-(const uint32 Val) const
			{
				return Shape(width - Val, height - Val, depth - Val, batch);
			};

			//Did not affect batch
			Shape operator*(const Shape &S) const
			{
				return Shape(width * S.width, height * S.height, depth * S.depth, batch);
			};
			Shape operator*(const uint32 Val) const
			{
				return Shape(width * Val, height * Val, depth * Val, batch);
			};

			uint32 Resolution() const
			{
				return width * height;
			};
			uint32 Volume() const
			{
				return Resolution() * depth;
			};
			uint32 Size() const
			{
				return Volume() * batch;
			};
		};
	}
}

#endif