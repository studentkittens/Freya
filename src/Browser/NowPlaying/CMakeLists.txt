IF(USE_GLYR)
    ADD_LIBRARY(FreyaNowPlayingLib STATIC 
        NowPlaying.cc
        ImageWall.cc
        EventImage.cc
        TextPageMgr.cc
        OtherAlbumsMgr.cc
        TracklistMgr.cc
        RelatedLinksMgr.cc
        TextItemsMgr.cc
        CoverArtMgr.cc
        ArtistPhotosMgr.cc
        )

    TARGET_LINK_LIBRARIES(FreyaNowPlayingLib FreyaGlyrLib)
ENDIF(USE_GLYR)
