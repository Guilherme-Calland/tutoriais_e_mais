package infrastructure

import "net/http"

type RemoteServiceRequestHandler struct {
	Invoker *server.Invoker //rafa resolverá
}

func (r *RemoteServiceRequestHandler) HandleInvokeRequest(writer http.ResponseWriter, request *http.Request) {

}
