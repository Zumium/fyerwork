{
    "targets": [
        {
            "target_name": "fyerwork",
            "include_dirs":[
                "<!(node -e \"require('nan')\")",
                "include"
            ],
            "sources": ["native/fyerwork.cc"]
        }
    ]
}
