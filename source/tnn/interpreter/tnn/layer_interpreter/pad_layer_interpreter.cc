// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "tnn/interpreter/tnn/layer_interpreter/abstract_layer_interpreter.h"

#include <limits.h>
#include <stdlib.h>

namespace TNN_NS {

DECLARE_LAYER_INTERPRETER(Pad, LAYER_PAD);

Status PadLayerInterpreter::InterpretProto(str_arr layer_cfg_arr, int start_index, LayerParam** param) {
    auto layer_param = new PadLayerParam();
    *param           = layer_param;
    int index        = start_index;

    if (index < layer_cfg_arr.size()) {
        int n1 = atoi(layer_cfg_arr[index++].c_str());
    }
    if (index < layer_cfg_arr.size()) {
        int n2 = atoi(layer_cfg_arr[index++].c_str());
    }

    int pad_h = INT_MIN;
    int pad_b = INT_MIN;
    int pad_w = INT_MIN;
    int pad_r = INT_MIN;
    if (index < layer_cfg_arr.size()) {
        pad_h = atoi(layer_cfg_arr[index++].c_str());
    }
    if (index < layer_cfg_arr.size()) {
        pad_b = atoi(layer_cfg_arr[index++].c_str());
    }
    if (index < layer_cfg_arr.size()) {
        pad_w = atoi(layer_cfg_arr[index++].c_str());
    }
    if (index < layer_cfg_arr.size()) {
        pad_r = atoi(layer_cfg_arr[index++].c_str());
    }

    if (index < layer_cfg_arr.size()) {
        int c1 = atoi(layer_cfg_arr[index++].c_str());
    }
    if (index < layer_cfg_arr.size()) {
        int c2 = atoi(layer_cfg_arr[index++].c_str());
    }
    if (index < layer_cfg_arr.size()) {
        layer_param->type = atoi(layer_cfg_arr[index++].c_str());
    }

    layer_param->pads = {pad_w, pad_r, pad_h, pad_b};
    return TNN_OK;
}

Status PadLayerInterpreter::InterpretResource(Deserializer& deserializer, LayerResource** resource) {
    return TNN_OK;
}

Status PadLayerInterpreter::SaveProto(std::ofstream& output_stream, LayerParam* param) {
    auto layer_param = dynamic_cast<PadLayerParam*>(param);
    if (nullptr == layer_param) {
        LOGE("invalid layer param to save\n");
        return Status(TNNERR_NULL_PARAM, "invalid layer param to save");
    }

    output_stream << "0 0 " << layer_param->pads[2] << " " << layer_param->pads[3] << " " << layer_param->pads[0] << " "
                  << layer_param->pads[1] << " 0 0 " << layer_param->type << " ";

    return TNN_OK;
}

Status PadLayerInterpreter::SaveResource(Serializer& serializer, LayerParam* param, LayerResource* resource) {
    return TNN_OK;
}

REGISTER_LAYER_INTERPRETER(Pad, LAYER_PAD);

}  // namespace TNN_NS
