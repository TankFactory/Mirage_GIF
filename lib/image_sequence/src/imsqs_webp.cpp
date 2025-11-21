#include "imsq_exception.h"
#include "imsq_stream.h"
#include "imsq_webp.cpp"

using namespace GIFImage;
using std::string;

class ImageSequenceStreamWebpImpl : public ImageSequenceStream {
  public:
    explicit ImageSequenceStreamWebpImpl(const string&);

    ~ImageSequenceStreamWebpImpl() override = default;

    Frame::Ref
    getNextFrame() noexcept override;

    [[nodiscard]] bool
    isEndOfStream() const noexcept override;

  private:
    ImageSequence::Ref m_imsq = nullptr;
    uint32_t m_currFrame      = 0;
};

ImageSequenceStreamWebpImpl::ImageSequenceStreamWebpImpl(const string& filename) {
    m_imsq = ImageSequence::read(filename);
    if (!m_imsq) {
        throw ImageParseException("Failed to read image sequence: " + filename);
    }
}

bool
ImageSequenceStreamWebpImpl::isEndOfStream() const noexcept {
    return m_currFrame >= m_imsq->getFrameCount();
}

Frame::Ref
ImageSequenceStreamWebpImpl::getNextFrame() noexcept {
    while (true) {
        if (isEndOfStream()) {
            return nullptr;
        }
        auto frame = m_imsq->getFrameBuffer(m_currFrame++, 0, 0);
        if (frame.empty()) {
            continue;
        }

        auto frameRef    = std::make_unique<Frame>();
        frameRef->buffer = std::move(frame);
        frameRef->width  = m_imsq->getWidth();
        frameRef->height = m_imsq->getHeight();
        frameRef->delay  = m_imsq->getDelays()[m_currFrame - 1];

        return frameRef;
    }
}