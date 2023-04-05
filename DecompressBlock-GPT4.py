def decompress_block(in_buf, block_header):
    # initialize LZSS parameters for this block
    N = 1 << (block_header.f - block_header.bits_for_len + 1)
    F = 1 << (block_header.bits_for_len)
    threshold = 3
    his_buf_pos = N - F

    his_buf = bytearray(N)
    out_buf = bytearray()
    out_buf_pos = 0

    in_buf_pos = 0

    # start extracting block contents
    while in_buf_pos < block_header.block_size - 1:
        # read bit field
        flags = in_buf[in_buf_pos]
        in_buf_pos += 1

        # process bit field
        for i in range(8):
            if in_buf_pos < block_header.block_size - 1:
                # check for buffer window reference
                if flags & 1 == 0:
                    # read offset and length
                    ofs_len = in_buf[in_buf_pos] + \
                        (in_buf[in_buf_pos + 1] << 8)
                    in_buf_pos += 2

                    # check for end marker
                    if ofs_len == 0:
                        break

                    # derive offset and length values
                    length = (ofs_len & block_header.length_mask) + threshold
                    offset = (his_buf_pos - (ofs_len >>
                              block_header.bits_for_len)) & (N - 1)

                    # peek into buffer
                    for j in range(length):
                        b = his_buf[(offset + j) & (N - 1)]
                        out_buf.append(b)
                        out_buf_pos += 1
                        his_buf[his_buf_pos] = b
                        his_buf_pos = (his_buf_pos + 1) & (N - 1)

                else:
                    # copy literally
                    b = in_buf[in_buf_pos]
                    in_buf_pos += 1
                    out_buf.append(b)
                    his_buf[his_buf_pos] = b
                    out_buf_pos += 1
                    his_buf_pos = (his_buf_pos + 1) & (N - 1)

                flags = flags >> 1

    return out_buf
