#include "TextureAtlas.h"

#include <gb/base/nullptr.h>

#include <set>
#include <map>
#include <cassert>

#include <gb/base/Atlas.h>

namespace
{
	using namespace gb::graphics;
	
	bool resizeFunc(int new_width, int new_height, void *user_data)
	{
		return true;
	}
}

namespace gb
{
	namespace graphics2d
	{
		
		using namespace base;
		using namespace containers;
		
		class TextureAtlas::TextureAtlasImpl
		{
		public:
			
			struct ImageBlockImpl : public ImageBlock
			{
				ImageBlockImpl(TextureAtlasImpl *parent) : parent(parent) {}
				
				virtual void destroyThis()
				{
					parent->releaseBlock(this);
				}
				
				TextureAtlasImpl *parent;
			};
			
			TextureAtlasImpl(Device &device) : device(device)
			{
				device.addRef();
			}
			
			~TextureAtlasImpl()
			{
				//assert(blocks.empty());
				device.release();
			}
			
			bool initialize(int tex_width, int tex_height)
			{
				if (!atlas)
				{
					atlas = boost::shared_ptr<Atlas>(new Atlas(tex_width, tex_height));
				}
				
				createTexture(tex_width, tex_height);
			}
			
			bool createTexture(int tex_width, int tex_height)
			{
				PTexture new_texture = device.createTexture(Texture::Texture2D);
				new_texture->setMinFilter(Texture::TF_LINEAR);
				new_texture->setMagFilter(Texture::TF_LINEAR);
				
				Image im;
				im.width = tex_width;
				im.height = tex_height;
				im.pixel_format = ePixelFormat::RGBA_8888;
				im.calculateDataSize();
				
				if(!new_texture->setImage(&im, 0))
					return false;
				
				texture = new_texture;
				return true;
			}
			
			const ImageBlock *createImageBlock(const containers::Image &image)
			{
				Rectangle rec;
				rec.width = image.width;
				rec.height = image.height;
				
				if (getBlock(rec))
				{
					return createImageBlock(image, rec);
				}
				else
				{
					boost::shared_ptr<Atlas> new_atlas = boost::shared_ptr<Atlas>(new Atlas(atlas->getWidth(), atlas->getHeight()));
					new_atlas->setResizeFunc(::resizeFunc, nullptr);
					std::vector<Rectangle> rects;
					rects.reserve(blocks.size() + 1);
					
					for (Blocks::iterator it = blocks.begin(); it != blocks.end(); ++it)
					{
						Rectangle im_rec;
						im_rec.width = (*it)->getImage().width;
						im_rec.height = (*it)->getImage().height;
						if (!new_atlas->insert(im_rec))
							return nullptr;
						rects.push_back(im_rec);
					}
					
					if (!new_atlas->insert(rec))
						return nullptr;
					rects.push_back(rec);
					
					if (!createTexture(new_atlas->getWidth(), new_atlas->getHeight()))
						return nullptr;
					
					new_atlas->setResizeFunc(nullptr, nullptr);
					atlas = new_atlas;
					
					size_t i = 0;
					for (Blocks::iterator it = blocks.begin(); it != blocks.end(); ++it, ++i)
					{
						Rectangle &rec = rects[i];
						*(Rectangle *) *it = rec;
						if (!texture->setSubImage(&(const Image &) **it, rec.left, rec.top, 0, 0))
							return nullptr;
					}
					
					return createImageBlock(image, rects[i]);
				}
				
				return nullptr;
			}
			
			const ImageBlock *createImageBlock(const containers::Image &image, const Rectangle &rec)
			{
				ImageBlockImpl *result = new ImageBlockImpl(this);
					
				*(Rectangle *) result = rec;
				result->copyFrom(image, image.pixel_format);
				
				if (!texture->setSubImage(&(const Image &) *result, rec.left, rec.top, 0, 0))
				{
					delete result;
					return nullptr;
				}
				blocks.insert(result);
				return result;
			}
			
			void releaseBlock(ImageBlockImpl *block)
			{
				blocks.erase(block);
				int id = (block->width << 16) + block->height;
				unused_blocks.insert(std::make_pair(id, *block));
				delete block;
			}
			
			base::RefCntHolder<graphics::Texture> getTexture()
			{
				return texture;
			}
			
		private:
			bool getBlock(Rectangle &rec)
			{
				// Сначала ищем неиспользуемые блоки, чей размер равен в точности требуемому
				int id = (rec.width << 16) + rec.height;
				UnusedBlocks::iterator it = unused_blocks.find(id);
				if (it != unused_blocks.end())
				{
					rec = it->second;
					unused_blocks.erase(it);
					return true;
				}
				
				return atlas->insert(rec);
			}
		
			Device &device;
			base::RefCntHolder<Texture> texture;
			boost::shared_ptr<base::Atlas> atlas;
			typedef std::set<ImageBlockImpl *> Blocks;
			Blocks blocks;
			typedef std::map<int, Rectangle> UnusedBlocks;
			UnusedBlocks unused_blocks;
		};
		
		TextureAtlas::TextureAtlas(Device& device)
		{
			pimpl = boost::shared_ptr<TextureAtlasImpl>(new TextureAtlasImpl(device));
		}
		
		bool TextureAtlas::initialize(int tex_width, int tex_height)
		{
			return pimpl->initialize(tex_width, tex_height);
		}
		
		const ImageBlock *TextureAtlas::createImageBlock(const containers::Image &image)
		{
			return pimpl->createImageBlock(image);
		}
		
		base::RefCntHolder<Texture> TextureAtlas::getTexture()
		{
			return pimpl->getTexture();
		}
	}
}
